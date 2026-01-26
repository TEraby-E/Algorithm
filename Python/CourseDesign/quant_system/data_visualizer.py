# modules/data_visualizer.py

import pandas as pd
import plotly.graph_objects as go
from plotly.subplots import make_subplots
import plotly.express as px
import numpy as np
import logging
import sys
from pathlib import Path
from typing import List, Dict, Tuple

# --- 路径修复 ---
# (保证模块可以独立运行或被 main.py 正常导入)
current_file_path = Path(__file__).resolve()
project_root = current_file_path.parent.parent
sys.path.append(str(project_root))

# 配置日志
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(name)s - %(levelname)s - %(message)s')
logger = logging.getLogger("DataVisualizer")


class DataVisualizer:

    def __init__(self, ma_periods: List[int] = [5, 10, 20]):
        """初始化可视化工具，设置默认的移动平均线周期"""
        self.ma_periods = ma_periods

    # --- 辅助计算私有方法 ---

    def _calculate_ma(self, df: pd.DataFrame) -> pd.DataFrame:
        """在 DataFrame 上计算移动平均线"""
        df_copy = df.copy()
        for p in self.ma_periods:
            df_copy[f'MA{p}'] = df_copy['close'].rolling(window=p, min_periods=1).mean()
        return df_copy

    def _calculate_returns(self, df: pd.DataFrame) -> pd.DataFrame:
        """计算累计收益率"""
        df_copy = df.copy()

        # 确保 'close' 列存在且是数值
        if 'close' not in df_copy.columns:
            logger.warning("DataFrame 缺少 'close' 列，无法计算收益率。")
            return pd.DataFrame()

        # 计算日收益率（使用 shift 避免依赖可能不存在的 pct_change 列）
        df_copy['daily_return'] = df_copy['close'].pct_change()

        # 计算累计收益率 (从 1 开始累乘)
        # 乘 100 转换为百分比
        df_copy['cumulative_return'] = (1 + df_copy['daily_return']).cumprod() - 1
        df_copy['cumulative_return'] *= 100

        # 确保日期是索引，方便绘图
        if 'date' in df_copy.columns:
            df_copy = df_copy.set_index('date')

        return df_copy

    # ----------------------------------------------------
    # 1. K线图 (带成交量和MA)
    # ----------------------------------------------------

    def plot_candlestick_and_volume(self, df: pd.DataFrame, symbol_name: str) -> go.Figure:
        """
        绘制交互式 K 线图、移动平均线和成交量图，使用 Plotly Subplots。
        """
        if df.empty:
            fig = go.Figure()
            fig.add_annotation(text=f"暂无 {symbol_name} 的数据", xref="paper", yref="paper", x=0.5, y=0.5,
                               showarrow=False, fontsize=20)
            return fig

        df_plot = self._calculate_ma(df)

        # 创建子图：rows=2 表示 K线图在上，成交量在下
        fig = make_subplots(rows=2, cols=1, shared_xaxes=True,
                            vertical_spacing=0.03,
                            row_heights=[0.7, 0.3])  # K线图占 70% 高度

        # 追踪 1: K线图
        fig.add_trace(go.Candlestick(x=df_plot['date'],
                                     open=df_plot['open'],
                                     high=df_plot['high'],
                                     low=df_plot['low'],
                                     close=df_plot['close'],
                                     name='K线',
                                     increasing_line_color='red',
                                     decreasing_line_color='green'),
                      row=1, col=1)

        # 追踪 2: 移动平均线 (MA)
        ma_colors = ['blue', 'orange', 'purple']  # 为 MA 赋予不同颜色
        for i, p in enumerate(self.ma_periods):
            fig.add_trace(go.Scatter(x=df_plot['date'],
                                     y=df_plot[f'MA{p}'],
                                     mode='lines',
                                     name=f'MA{p}',
                                     line=dict(width=1.5, color=ma_colors[i % len(ma_colors)])),
                          row=1, col=1)

        # 追踪 3: 成交量图 (颜色根据收盘价涨跌)
        colors = ['red' if c >= o else 'green' for c, o in zip(df_plot['close'], df_plot['open'])]
        fig.add_trace(go.Bar(x=df_plot['date'],
                             y=df_plot['volume'],
                             name='成交量',
                             marker_color=colors,
                             opacity=0.7),
                      row=2, col=1)

        # 布局设置
        fig.update_layout(
            title=f"**{symbol_name}** K线与成交量分析",
            xaxis_rangeslider_visible=False,
            hovermode="x unified",
            height=650,
            template="plotly_white",
            legend=dict(orientation="h", yanchor="bottom", y=1.02, xanchor="right", x=1)
        )

        # 更新轴设置
        fig.update_xaxes(title_text="", row=1, col=1, showgrid=True)
        fig.update_xaxes(title_text="日期", row=2, col=1)
        fig.update_yaxes(title_text="价格", row=1, col=1)
        fig.update_yaxes(title_text="成交量", row=2, col=1)

        return fig

    # ----------------------------------------------------
    # 2. 收益率分析图表
    # ----------------------------------------------------

    def plot_return_analysis(self, df: pd.DataFrame, symbol_name: str) -> go.Figure:
        """绘制单个资产的累计收益率图表"""
        df_plot = self._calculate_returns(df)

        if df_plot.empty:
            return go.Figure().add_annotation(text="暂无数据", showarrow=False)

        fig = go.Figure()
        fig.add_trace(go.Scatter(x=df_plot.index,
                                 y=df_plot['cumulative_return'],
                                 mode='lines',
                                 name=symbol_name,
                                 line=dict(width=3, color='royalblue')))

        fig.update_layout(
            title=f"**{symbol_name}** 累计收益率 ({df_plot.index.min().strftime('%Y/%m/%d')} 至 {df_plot.index.max().strftime('%Y/%m/%d')})",
            xaxis_title="日期",
            yaxis_title="累计收益率 (%)",
            hovermode="x unified",
            template="plotly_white"
        )
        # 增加一条 Y=0 的线，便于观察收益率正负
        fig.add_hline(y=0, line_dash="dash", line_color="gray")
        return fig

    # ----------------------------------------------------
    # 3. 多股票对比图
    # ----------------------------------------------------

    def plot_multi_stock_comparison(self, data_dict: Dict[str, pd.DataFrame], name_map: Dict[str, str]) -> go.Figure:
        """
        绘制多只股票的标准化收益率对比图
        :param data_dict: 字典 {symbol: DataFrame}
        :param name_map: 字典 {symbol: name} 用于显示
        """
        if not data_dict:
            return go.Figure().add_annotation(text="暂无数据进行对比", showarrow=False)

        combined_returns = pd.DataFrame()

        for symbol, df in data_dict.items():
            if df.empty: continue

            df_returns = self._calculate_returns(df)
            if df_returns.empty: continue

            # 标准化：将起始点的累计收益率设为 0%
            normalized_series = df_returns['cumulative_return'] - df_returns['cumulative_return'].iloc[0]

            # 使用友好名称作为列名
            combined_returns[name_map.get(symbol, symbol)] = normalized_series

        # 确保日期对齐（使用最新的时间范围）
        combined_returns = combined_returns.sort_index().dropna(how='all')

        fig = px.line(combined_returns,
                      x=combined_returns.index,
                      y=combined_returns.columns,
                      title="多资产标准化累计收益率对比 (起始点归一化为 0%)",
                      labels={"value": "累计收益率 (%)", "variable": "资产"},
                      template="plotly_dark")

        fig.update_layout(hovermode="x unified")
        fig.add_hline(y=0, line_dash="dash", line_color="gray")
        return fig

    # ----------------------------------------------------
    # 4. 相关性热力图
    # ----------------------------------------------------

    def plot_correlation_heatmap(self, data_dict: Dict[str, pd.DataFrame], name_map: Dict[str, str]) -> go.Figure:
        """
        绘制多只股票收盘价日收益率的相关性热力图
        :param data_dict: 字典 {symbol: DataFrame}
        :param name_map: 字典 {symbol: name} 用于显示
        """
        if not data_dict or len(data_dict) < 2:
            fig = go.Figure()
            fig.add_annotation(text="至少需要两只股票的数据才能计算相关性", showarrow=False)
            return fig

        # 1. 提取所有股票的日收益率
        daily_returns = pd.DataFrame()
        for symbol, df in data_dict.items():
            if not df.empty:
                df_returns = self._calculate_returns(df)
                if not df_returns.empty:
                    # 使用友好名称作为列名
                    daily_returns[name_map.get(symbol, symbol)] = df_returns['daily_return']

        # 2. 计算相关性矩阵
        correlation_matrix = daily_returns.corr().round(4)

        # 3. 绘制热力图
        fig = px.imshow(correlation_matrix,
                        text_auto=True,
                        aspect="auto",
                        color_continuous_scale=px.colors.diverging.RdBu)

        fig.update_layout(
            title="股票日收益率相关性热力图",
            height=500
        )
        fig.update_xaxes(tickangle=45, title="")
        fig.update_yaxes(title="")
        fig.update_coloraxes(colorbar_title="相关性", cmin=-1, cmax=1)

        return fig

    # ----------------------------------------------------
    # 5. 数据统计摘要表
    # ----------------------------------------------------

    def generate_statistics_table(self, df: pd.DataFrame, symbol_name: str) -> pd.DataFrame:
        """
        生成股票数据的关键统计摘要表 (均值，标准差，最大值等)
        """
        if df.empty:
            return pd.DataFrame({"提示": ["暂无数据进行统计"]})

        # 只对核心数值列进行统计
        stats = df[['open', 'close', 'high', 'low', 'volume', 'pct_change']].describe().transpose()

        # 计算额外指标
        df_returns = self._calculate_returns(df)

        # 1. 累计总收益率
        total_return = df_returns['cumulative_return'].iloc[-1] if not df_returns.empty else np.nan

        # 2. 年化收益率 (简单计算：假设数据为交易日，年化因子252)
        days = (df_returns.index.max() - df_returns.index.min()).days
        annual_factor = 365 / days if days > 0 else 0
        annual_return = total_return * annual_factor

        # 构建新的指标 DataFrame
        custom_metrics = pd.DataFrame({
            '指标': ['总累计收益率 (%)', '年化收益率 (%)', '最大收盘价', '最小收盘价'],
            '值': [total_return, annual_return, stats.loc['close', 'max'], stats.loc['close', 'min']]
        })

        # 提取关键统计量
        basic_stats = stats.loc[['close', 'volume', 'pct_change'], ['mean', 'std']]
        basic_stats = basic_stats.rename(columns={'mean': '均值', 'std': '标准差'}).reset_index().rename(
            columns={'index': '指标'})

        # 合并并格式化
        basic_stats = basic_stats.melt(id_vars='指标', var_name='统计量', value_name='值')

        # 最终合并和整理
        final_table = pd.concat([custom_metrics, basic_stats], ignore_index=True)
        final_table = final_table.drop_duplicates(subset=['指标'])

        final_table['股票'] = symbol_name

        # 格式化输出 (保留4位小数，百分比带 % 符号)
        final_table['值'] = final_table['值'].apply(
            lambda x: f"{x:.4f}" if isinstance(x, (int, float)) and x != 0 else x)

        # 调整列顺序，使其更适合 Streamlit 展示
        final_table = final_table[['股票', '指标', '值']]

        return final_table