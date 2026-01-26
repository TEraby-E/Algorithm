# modules/akshare_fetcher.py

import akshare as ak
import pandas as pd
import logging
import time
import random  # 新增
import requests
from typing import Optional, Dict, List
import sys
import os
from pathlib import Path

# 路径修复
current_file_path = Path(__file__).resolve()
project_root = current_file_path.parent.parent
sys.path.append(str(project_root))
from config.settings import REPRESENTATIVE_STOCKS, COLUMN_MAPPING

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')
logger = logging.getLogger("AkshareFetcher")


class AkshareFetcher:
    # 新增 proxies 参数到构造函数
    def __init__(self, retry_count: int = 3, retry_delay: float = 2.0, proxies: Optional[Dict[str, str]] = None):
        self.retry_count = retry_count
        self.retry_delay = retry_delay  # <--- 新增此行

        # 代理配置，格式如 {"http": "http://127.0.0.1:1080", "https": "http://127.0.0.1:1080"}
        self.proxies = proxies

        # --- 爬虫伪装配置 ---
        self.user_agents = [
            # ... (User-Agents 列表不变) ...
        ]

    # ... (_get_random_headers 和 _random_sleep 保持不变) ...

    def _fetch_with_retry(self, func, *args, **kwargs):
        """带重试和伪装的执行器"""
        last_exception = None

        # 准备 kwargs，加入代理设置
        fetch_kwargs = kwargs.copy()
        if self.proxies:
            # akshare 内部 API 接受 **kwargs，我们将其代理配置传进去
            fetch_kwargs['proxies'] = self.proxies

        for attempt in range(self.retry_count):
            try:
                self._random_sleep()

                # 传入代理设置
                return func(*args, **fetch_kwargs)
            except Exception as e:
                last_exception = e
                logger.warning(f"Attempt {attempt + 1}/{self.retry_count} failed: {str(e)}")
                # 失败后使用 self.retry_delay
                time.sleep(self.retry_delay)

        logger.error(f"All retry attempts failed. Last error: {str(last_exception)}")
        return pd.DataFrame()

    def fetch_stock_data(self, symbol: str, start_date: str, end_date: str, adjust: str = "qfq") -> pd.DataFrame:
        logger.info(f"Fetching {symbol}...")

        def _api_call(proxies: Optional[Dict[str, str]] = None):  # 新增 proxies 参数
            # akshare 库的 API 调用
            return ak.stock_zh_a_hist(
                symbol=symbol, period="daily", start_date=start_date, end_date=end_date,
                adjust=adjust, proxies=proxies  # <--- 将代理参数传递给 akshare
            )

        # 在这里调用 _fetch_with_retry，它会自动处理代理配置
        df = self._fetch_with_retry(_api_call)

        if not df.empty:
            return df

    # --- 辅助功能 ---
    def _get_random_headers(self):
        """生成随机请求头"""
        return {
            "User-Agent": random.choice(self.user_agents),
            "Accept-Language": "zh-CN,zh;q=0.9,en;q=0.8"
        }

    def _random_sleep(self):
        """随机延迟 0.5 ~ 2 秒，避免触发频率限制"""
        time.sleep(random.uniform(0.5, 2.0))

    def _fetch_with_retry(self, func, *args, **kwargs):
            """带重试和伪装的执行器"""
            last_exception = None

            for attempt in range(self.retry_count):
                try:
                    # 在每次请求前进行伪装处理 (Akshare 内部主要使用 requests，我们可以尝试通过环境变量或monkey patch影响它，
                    # 但最简单有效的是控制频率。Akshare 某些接口允许传 headers，但大多数封装好了。
                    # 核心策略：控制频率 + 随机等待)
                    self._random_sleep()

                    return func(*args, **kwargs)
                except Exception as e:
                    last_exception = e
                    logger.warning(f"Attempt {attempt + 1}/{self.retry_count} failed: {str(e)}")
                    time.sleep(2)  # 失败后强制等待更久

            logger.error(f"All retry attempts failed. Last error: {str(last_exception)}")
            return pd.DataFrame()

    def fetch_stock_data(self, symbol: str, start_date: str, end_date: str, adjust: str = "qfq") -> pd.DataFrame:
        # (保持原有逻辑不变，只要调用了 _fetch_with_retry 即可)
        logger.info(f"Fetching {symbol}...")

        def _api_call():
            # 这里不需要手动传 headers，akshare 内部已处理，我们主要靠 _random_sleep 规避频率限制
            return ak.stock_zh_a_hist(
                symbol=symbol, period="daily", start_date=start_date, end_date=end_date, adjust=adjust
            )

        df = self._fetch_with_retry(_api_call)

        if not df.empty:
            df = df.rename(columns=COLUMN_MAPPING)
            if 'date' in df.columns:
                df['date'] = pd.to_datetime(df['date']).dt.date
            df['symbol'] = symbol

        return df

    def fetch_multiple_stocks(self, symbols: List[str], start_date: str, end_date: str, adjust: str = "qfq") -> Dict[
        str, pd.DataFrame]:
        results = {}
        for sym in symbols:
            df = self.fetch_stock_data(sym, start_date, end_date, adjust)
            if not df.empty:
                results[sym] = df
        return results

    def normalize_symbol(self, symbol: str) -> str:
        """标准化股票代码为6位数字字符串"""
        if isinstance(symbol, int):
            return f"{symbol:06d}"
        return str(symbol).strip().zfill(6)

    def validate_symbol(self, symbol: str) -> bool:
        """
        验证股票代码是否在支持的列表(10个代表股)中
        注意：实际生产环境中可能需要查全量表，这里按需求简化
        """
        norm_symbol = self.normalize_symbol(symbol)
        return norm_symbol in REPRESENTATIVE_STOCKS

    def get_stock_info(self, symbol: str) -> Dict[str, str]:
        """获取股票基本信息"""
        norm_symbol = self.normalize_symbol(symbol)
        name = REPRESENTATIVE_STOCKS.get(norm_symbol)
        
        if name:
            return {"symbol": norm_symbol, "name": name, "valid": True}
        else:
            return {"symbol": norm_symbol, "name": "未知/不支持", "valid": False}

    def get_available_symbols(self) -> Dict[str, str]:
        """获取所有可用股票列表"""
        return REPRESENTATIVE_STOCKS

    def search_symbols(self, keyword: str) -> Dict[str, str]:
        """根据代码或名称搜索股票"""
        result = {}
        for code, name in REPRESENTATIVE_STOCKS.items():
            if keyword in code or keyword in name:
                result[code] = name
        return result

    # --- 核心数据获取 ---

    def _fetch_with_retry(self, func, *args, **kwargs):
        """内部私有方法：执行带重试机制的函数调用"""
        last_exception = None
        
        for attempt in range(self.retry_count):
            try:
                return func(*args, **kwargs)
            except Exception as e:
                last_exception = e
                logger.warning(f"Attempt {attempt + 1}/{self.retry_count} failed: {str(e)}")
                if attempt < self.retry_count - 1:
                    time.sleep(self.retry_delay)
        
        logger.error(f"All retry attempts failed. Last error: {str(last_exception)}")
        return pd.DataFrame() # 失败返回空DataFrame

    def fetch_stock_data(self, 
                         symbol: str, 
                         start_date: str = '20230101', 
                         end_date: str = '20231231', 
                         adjust: str = "qfq") -> pd.DataFrame:
        """
        获取股票历史数据
        :param symbol: 股票代码 (e.g., '600519')
        :param start_date: 开始日期 'YYYYMMDD'
        :param end_date: 结束日期 'YYYYMMDD'
        :param adjust: 复权方式 'qfq'(前复权), 'hfq'(后复权), ''(不复权)
        :return: 清洗后的DataFrame
        """
        symbol = self.normalize_symbol(symbol)
        
        if not self.validate_symbol(symbol):
            logger.error(f"Invalid symbol: {symbol}")
            return pd.DataFrame()

        logger.info(f"Fetching data for {symbol} ({REPRESENTATIVE_STOCKS[symbol]})...")

        def _api_call():
            # akshare 接口: stock_zh_a_hist
            return ak.stock_zh_a_hist(
                symbol=symbol, 
                period="daily", 
                start_date=start_date, 
                end_date=end_date, 
                adjust=adjust
            )

        df = self._fetch_with_retry(_api_call)
        
        if not df.empty:
            # 数据清洗：重命名列，转换日期格式
            df = df.rename(columns=COLUMN_MAPPING)
            if 'date' in df.columns:
                df['date'] = pd.to_datetime(df['date']).dt.date
            
            # 确保包含股票代码列，方便合并
            df['symbol'] = symbol
            logger.info(f"Successfully fetched {len(df)} records for {symbol}")
        
        return df

    def fetch_index_data(self, symbol: str = "sh000001") -> pd.DataFrame:
        """
        获取指数数据 (默认为上证指数)
        """
        logger.info(f"Fetching index data for {symbol}...")
        
        def _api_call():
            # akshare 接口: stock_zh_index_daily (以sh000001为例)
            return ak.stock_zh_index_daily(symbol=symbol)
        
        df = self._fetch_with_retry(_api_call)
        
        if not df.empty:
            df = df.rename(columns=COLUMN_MAPPING)
            if 'date' in df.columns:
                df['date'] = pd.to_datetime(df['date']).dt.date
            df['symbol'] = symbol
            logger.info(f"Successfully fetched {len(df)} records for index {symbol}")

        return df

    def fetch_multiple_stocks(self, 
                              symbols: List[str], 
                              start_date: str, 
                              end_date: str,
                              adjust: str = "qfq") -> Dict[str, pd.DataFrame]:
        """
        批量获取股票数据
        :return: 字典 {symbol: DataFrame}
        """
        results = {}
        for sym in symbols:
            df = self.fetch_stock_data(sym, start_date, end_date, adjust)
            if not df.empty:
                results[sym] = df
            # 避免请求过快触发反爬限制
            time.sleep(0.5) 
            
        return results

# --- 测试代码 ---
if __name__ == "__main__":
    # 简单的本地测试
    fetcher = AkshareFetcher()
    
    # 1. 测试获取单个股票 (贵州茅台)
    df_maotai = fetcher.fetch_stock_data("600519", start_date="20231001", end_date="20231101")
    print(f"\n茅台数据预览:\n{df_maotai.head()}")
    
    # 2. 测试代码搜索
    print(f"\n搜索 '比亚迪': {fetcher.search_symbols('比亚迪')}")
    
    # 3. 测试获取指数
    df_index = fetcher.fetch_index_data("sh000001")
    print(f"\n上证指数预览:\n{df_index.tail()}")