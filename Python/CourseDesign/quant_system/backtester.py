# modules/backtester.py

import pandas as pd
import numpy as np
import plotly.graph_objects as go
import logging

logger = logging.getLogger("Backtester")


class Backtester:
    def __init__(self, initial_capital: float = 100000.0, commission: float = 0.0003):
        self.initial_capital = initial_capital
        self.commission = commission  # 佣金率 (万3)

    def run_strategy(self, df: pd.DataFrame, strategy_type: str = "SMA_Cross"):
        """
        运行回测
        :param strategy_type: 'SMA_Cross' (双均线) 或 'ML_Signal' (机器学习信号)
        """
        if df.empty: return None

        df = df.copy()
        df['date'] = pd.to_datetime(df['date'])
        df = df.set_index('date')

        # 1. 生成交易信号 (1: 买入/持有, 0: 空仓/卖出)
        if strategy_type == "SMA_Cross":
            # 简单双均线策略：5日线上穿20日线买入
            df['SMA_5'] = df['close'].rolling(window=5).mean()
            df['SMA_20'] = df['close'].rolling(window=20).mean()
            df['Signal'] = np.where(df['SMA_5'] > df['SMA_20'], 1, 0)
            # 信号平移一天（因为今天的信号只能明天执行）
            df['Position'] = df['Signal'].shift(1)

        elif strategy_type == "Buy_Hold":
            df['Position'] = 1  # 始终持有

        # 2. 计算收益
        # 每日涨跌幅
        df['Market_Return'] = df['close'].pct_change()

        # 策略收益 = 持仓状态 * 市场收益
        # 注意：这里简化了模型，假设全仓买入
        df['Strategy_Return'] = df['Position'] * df['Market_Return']

        # 扣除交易成本 (当 Position 发生变化时产生成本)
        df['Trade_Action'] = df['Position'].diff().abs()
        df['Strategy_Return'] = df['Strategy_Return'] - (df['Trade_Action'] * self.commission)

        # 3. 计算资金曲线
        df['Cumulative_Market'] = (1 + df['Market_Return']).cumprod() * self.initial_capital
        df['Cumulative_Strategy'] = (1 + df['Strategy_Return']).cumprod() * self.initial_capital

        # 填充 NaN
        df.fillna(method='bfill', inplace=True)

        return self._calculate_metrics(df)

    def _calculate_metrics(self, df: pd.DataFrame):
        """计算回测指标"""
        # 总收益率
        total_return = (df['Cumulative_Strategy'].iloc[-1] / self.initial_capital) - 1

        # 年化收益
        days = (df.index[-1] - df.index[0]).days
        annual_return = (1 + total_return) ** (365 / days) - 1 if days > 0 else 0

        # 最大回撤
        cumulative = df['Cumulative_Strategy']
        running_max = cumulative.cummax()
        drawdown = (cumulative - running_max) / running_max
        max_drawdown = drawdown.min()

        # 夏普比率 (假设无风险利率 3%)
        risk_free_rate = 0.03
        excess_returns = df['Strategy_Return'] - (risk_free_rate / 252)
        sharpe_ratio = np.sqrt(252) * excess_returns.mean() / excess_returns.std()

        return {
            "df": df,
            "total_return": total_return,
            "annual_return": annual_return,
            "max_drawdown": max_drawdown,
            "sharpe_ratio": sharpe_ratio
        }

    def plot_results(self, metrics: dict):
        """绘制资金曲线图"""
        df = metrics['df']

        fig = go.Figure()

        # 策略净值
        fig.add_trace(go.Scatter(
            x=df.index, y=df['Cumulative_Strategy'],
            mode='lines', name='策略净值 (Strategy)',
            line=dict(color='red', width=2)
        ))

        # 基准净值 (买入持有)
        fig.add_trace(go.Scatter(
            x=df.index, y=df['Cumulative_Market'],
            mode='lines', name='基准净值 (Benchmark)',
            line=dict(color='gray', width=1, dash='dash')
        ))

        fig.update_layout(
            title="策略回测资金曲线",
            xaxis_title="日期",
            yaxis_title="账户净值",
            hovermode="x unified",
            template="plotly_white"
        )
        return fig