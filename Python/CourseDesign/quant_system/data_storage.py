# modules/data_storage.py

import sqlite3
import pandas as pd
import os
import sys
import logging
from pathlib import Path
from datetime import datetime

# --- 路径修复 (同 akshare_fetcher) ---
current_file_path = Path(__file__).resolve()
current_dir = current_file_path.parent
project_root = current_dir.parent
sys.path.append(str(project_root))

from config.settings import COLUMN_MAPPING

# 配置日志
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')
logger = logging.getLogger("DataStorage")

class DataStorage:
    def __init__(self, db_name: str = "quant_data.db", csv_dir: str = "data_csv"):
        """
        初始化数据存储模块
        :param db_name: SQLite数据库文件名
        :param csv_dir: CSV文件存储目录
        """
        # 设定数据存储目录
        self.data_dir = project_root / "data"
        if not self.data_dir.exists():
            self.data_dir.mkdir(parents=True)

        self.db_path = self.data_dir / db_name
        self.csv_dir = self.data_dir / csv_dir
        
        if not self.csv_dir.exists():
            self.csv_dir.mkdir(parents=True)

        self.table_name = "stock_daily"
        self._init_db()

    def _get_conn(self):
        """获取数据库连接"""
        return sqlite3.connect(str(self.db_path))

    def _init_db(self):
        """初始化数据库表结构"""
        conn = self._get_conn()
        cursor = conn.cursor()
        
        # 创建日线行情表
        # 使用 symbol 和 date 作为联合主键，防止重复
        create_table_sql = f"""
        CREATE TABLE IF NOT EXISTS {self.table_name} (
            symbol TEXT,
            date TEXT,
            open REAL,
            close REAL,
            high REAL,
            low REAL,
            volume REAL,
            amount REAL,
            amplitude REAL,
            pct_change REAL,
            change REAL,
            turnover REAL,
            PRIMARY KEY (symbol, date)
        );
        """
        try:
            cursor.execute(create_table_sql)
            conn.commit()
            logger.info("Database initialized successfully.")
        except Exception as e:
            logger.error(f"Database initialization failed: {e}")
        finally:
            conn.close()

    def save_data(self, df: pd.DataFrame, symbol: str):
        """
        保存数据到 SQLite 和 CSV
        :param df: 标准化后的 DataFrame
        :param symbol: 股票代码
        """
        if df is None or df.empty:
            logger.warning(f"No data to save for {symbol}")
            return

        # 1. 确保日期格式为字符串 (YYYY-MM-DD) 存入 SQLite
        # 复制一份以免修改原始引用
        save_df = df.copy()
        if 'date' in save_df.columns:
             # 如果是 datetime 对象，转为字符串；如果是字符串，保持不变
            save_df['date'] = save_df['date'].astype(str)

        # 2. 保存到 SQLite (处理重复：先删后插)
        self._save_to_sqlite(save_df, symbol)

        # 3. 保存到 CSV (覆盖模式)
        self._save_to_csv(save_df, symbol)

    def _save_to_sqlite(self, df: pd.DataFrame, symbol: str):
        conn = self._get_conn()
        try:
            # 获取数据的时间范围
            min_date = df['date'].min()
            max_date = df['date'].max()

            # 事务开始：先删除该时间段内的旧数据，防止主键冲突
            delete_sql = f"DELETE FROM {self.table_name} WHERE symbol = ? AND date >= ? AND date <= ?"
            conn.execute(delete_sql, (symbol, min_date, max_date))
            
            # 写入新数据
            df.to_sql(self.table_name, conn, if_exists='append', index=False)
            conn.commit()
            logger.info(f"Saved {len(df)} records for {symbol} to SQLite.")
        except Exception as e:
            conn.rollback()
            logger.error(f"Failed to save to SQLite: {e}")
        finally:
            conn.close()

    def _save_to_csv(self, df: pd.DataFrame, symbol: str):
        file_path = self.csv_dir / f"{symbol}.csv"
        try:
            # 检查文件是否存在，如果存在则追加，否则新建
            # 注意：简单的追加可能导致CSV中有重复行，
            # 这里的策略是：为了简单起见，按全量覆盖保存最新的一批数据，
            # 或者你可以读取旧CSV合并。为了项目简洁，这里采用覆盖/追加逻辑。
            
            # 如果是全量更新，直接 overwrite
            if file_path.exists():
                # 读取旧数据合并（可选，这里简化为追加模式，但需注意重复）
                # 生产环境建议：读取旧csv -> concat -> drop_duplicates -> save
                pass
            
            # 简化策略：直接保存本次获取的数据为独立文件，或者追加
            # 考虑到数据完整性，最稳健的方式是每次都Dump数据库的数据导出CSV
            # 这里仅演示将本次 df 存入
            df.to_csv(file_path, index=False, encoding='utf-8-sig') 
            logger.info(f"Saved CSV for {symbol}")
        except Exception as e:
            logger.error(f"Failed to save CSV: {e}")

    def load_data(self, symbol: str, start_date: str = None, end_date: str = None) -> pd.DataFrame:
        """
        从数据库读取数据
        """
        conn = self._get_conn()
        query = f"SELECT * FROM {self.table_name} WHERE symbol = ?"
        params = [symbol]

        if start_date:
            query += " AND date >= ?"
            params.append(start_date)
        if end_date:
            query += " AND date <= ?"
            params.append(end_date)
        
        query += " ORDER BY date ASC"

        try:
            df = pd.read_sql(query, conn, params=params)
            if not df.empty:
                # 转换日期列回 datetime 对象，方便 Pandas 处理
                df['date'] = pd.to_datetime(df['date'])
            return df
        except Exception as e:
            logger.error(f"Error loading data: {e}")
            return pd.DataFrame()
        finally:
            conn.close()

    def get_latest_date(self, symbol: str) -> str:
        """
        检查数据库中某股票的最新日期，用于增量更新
        :return: 'YYYY-MM-DD' or None
        """
        conn = self._get_conn()
        cursor = conn.cursor()
        try:
            cursor.execute(f"SELECT MAX(date) FROM {self.table_name} WHERE symbol = ?", (symbol,))
            result = cursor.fetchone()
            return result[0] if result[0] else None
        except Exception as e:
            logger.error(f"Error checking update date: {e}")
            return None
        finally:
            conn.close()

# --- 测试代码 ---
if __name__ == "__main__":
    # 模拟数据
    data = {
        'symbol': ['000001', '000001'],
        'date': ['2023-01-01', '2023-01-02'],
        'open': [10.0, 10.5],
        'close': [10.5, 11.0],
        'high': [11.0, 11.2],
        'low': [9.8, 10.3],
        'volume': [1000, 1200],
        'amount': [10000, 13000],
        'pct_change': [1.2, 0.5],
        'turnover': [0.1, 0.12]
    }
    df_test = pd.DataFrame(data)

    storage = DataStorage()
    
    # 1. 测试保存
    print("Testing Save...")
    storage.save_data(df_test, "000001")
    
    # 2. 测试获取最新日期
    latest = storage.get_latest_date("000001")
    print(f"Latest date in DB: {latest}")
    
    # 3. 测试读取
    print("Testing Load...")
    df_load = storage.load_data("000001")
    print(df_load)
    
    print(f"\n数据库位置: {storage.db_path}")