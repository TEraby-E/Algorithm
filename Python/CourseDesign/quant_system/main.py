# main.py

import streamlit as st
import pandas as pd
from datetime import datetime, timedelta

# 导入所有核心模块
from akshare_fetcher import AkshareFetcher
from data_storage import DataStorage
from data_visualizer import DataVisualizer
from config.settings import REPRESENTATIVE_STOCKS, MARKET_INDICES
from model_predictor import MarketPredictor
from backtester import Backtester
from typing import Optional, Dict # <--- 新增此行
# 初始化所有核心类 (使用 Streamlit 的缓存机制)
@st.cache_resource
def init_modules(proxies: Optional[Dict[str, str]] = None):
    """初始化并缓存模块实例"""
    # 将代理参数传递给 AkshareFetcher
    return AkshareFetcher(proxies=proxies), DataStorage(), DataVisualizer(), MarketPredictor(), Backtester()
fetcher, storage, visualizer, predictor, backtester = init_modules()
# --- 1. 数据更新与缓存函数 ---
def load_data_and_update(symbol, adjust, time_period_days):
    # 这里直接复用之前的代码逻辑
    end_date_str = datetime.now().strftime("%Y%m%d")
    start_date = datetime.now() - timedelta(days=time_period_days)
    start_date_str = start_date.strftime("%Y%m%d")

    df_db = storage.load_data(symbol, start_date.strftime('%Y-%m-%d'), datetime.now().strftime('%Y-%m-%d'))

    needs_update = df_db.empty or df_db['date'].max().date() < datetime.now().date()

    if needs_update:
        st.info(f"正在获取 {symbol} 数据...")
        try:
            df_new = fetcher.fetch_stock_data(symbol, start_date=start_date_str, end_date=end_date_str, adjust=adjust)
        except Exception as e:
            st.error(f"获取失败: {e}")
            return df_db

        if not df_new.empty:
            storage.save_data(df_new, symbol)
            return df_new
        else:
            return df_db
    else:
        return df_db


def render_proxy_input():
    st.sidebar.subheader("网络代理 (Proxy)")

    proxy_url = st.sidebar.text_input(
        "输入代理地址 (格式: IP:Port 或 User:Pass@IP:Port)",
        key="proxy_input"
    )

    proxy_dict = None
    if proxy_url:
        try:
            proxy_dict = {
                "http": f"http://{proxy_url}",
                "https": f"http://{proxy_url}",
            }
            st.sidebar.success("代理已启用")
        except Exception:
            st.sidebar.error("代理格式错误")

    # 统一出口
    st.session_state["proxies"] = proxy_dict



# --- 2. Streamlit UI 布局 ---
def setup_sidebar():
    st.sidebar.title("🛠️ 参数设置")
    st.sidebar.markdown("---")

    # 代理配置（只在这里）
    render_proxy_input()

    st.sidebar.markdown("---")

    stock_options = {v: k for k, v in REPRESENTATIVE_STOCKS.items()}

    # 功能选择
    st.sidebar.selectbox(
        "选择功能模块",
        ["数据看板", "AI 价格预测", "策略回测"],
        key="app_mode"
    )

    # 股票选择
    default_stock = "贵州茅台"
    st.sidebar.selectbox(
        "选择股票",
        list(stock_options.keys()),
        index=list(stock_options.keys()).index(default_stock),
        key="stock_name"
    )

    st.session_state["selected_symbol"] = stock_options[
        st.session_state["stock_name"]
    ]

    # 时间周期
    st.session_state["time_period_days"] = (
        365 if st.session_state["app_mode"] == "数据看板" else 1095
    )

def main():
    st.set_page_config(page_title="量化分析系统 Pro", layout="wide")

    setup_sidebar()

    proxies = st.session_state.get("proxies")

    global fetcher, storage, visualizer, predictor, backtester

    if (
        "initialized_proxies" not in st.session_state
        or st.session_state["initialized_proxies"] != proxies
    ):
        fetcher, storage, visualizer, predictor, backtester = init_modules(
            proxies=proxies
        )
        st.session_state["initialized_proxies"] = proxies

    mode = st.session_state["app_mode"]
    symbol_name = st.session_state["stock_name"]
    symbol = st.session_state["selected_symbol"]

    df = load_data_and_update(
        symbol, "qfq", st.session_state["time_period_days"]
    )
    if df.empty:
        st.error("暂无数据，请检查网络或更换股票。")
        return

    st.title(f"{symbol_name} - {mode}")

    # --- 模块 1: 数据看板 ---
    if mode == "数据看板":
        k_fig = visualizer.plot_candlestick_and_volume(df, symbol_name)
        st.plotly_chart(k_fig, use_container_width=True)

        stats = visualizer.generate_statistics_table(df, symbol_name)
        st.table(stats)

    # --- 模块 2: AI 价格预测 ---
    elif mode == "AI 价格预测":
        st.markdown("### 🤖 基于随机森林 (Random Forest) 的趋势预测")
        st.info("说明：模型使用 MACD, RSI, 布林带等技术指标作为特征，预测'下一个交易日'是否上涨。")

        if st.button("开始训练并预测"):
            with st.spinner("正在进行特征工程和模型训练..."):
                results = predictor.train_and_evaluate(df)

                if results:
                    col1, col2, col3 = st.columns(3)
                    col1.metric("测试集准确率 (Accuracy)", f"{results['accuracy']:.2%}")

                    # 预测明日
                    next_day = predictor.predict_next_day(df)
                    col2.metric("明日预测", next_day['prediction'])
                    col3.metric("上涨概率", f"{next_day['probability_up']:.2%}")

                    # 特征重要性
                    st.subheader("特征重要性")
                    st.bar_chart(results['feature_importance'].set_index('feature'))

                    # 详细报告
                    with st.expander("查看详细分类报告"):
                        st.json(results['report'])
                else:
                    st.warning("数据不足，无法训练模型。")

    # --- 模块 3: 策略回测 ---
    elif mode == "策略回测":
        st.markdown("### 🔙 交易策略历史回测")

        strategy = st.radio("选择策略", ["双均线策略 (MA5 cross MA20)", "买入持有 (Buy & Hold)"])
        strategy_code = "SMA_Cross" if "双均线" in strategy else "Buy_Hold"

        initial_cap = st.number_input("初始资金", value=100000)

        if st.button("开始回测"):
            backtester.initial_capital = initial_cap
            metrics = backtester.run_strategy(df, strategy_code)

            if metrics:
                # 展示核心指标
                c1, c2, c3, c4 = st.columns(4)
                c1.metric("总收益率", f"{metrics['total_return']:.2%}")
                c2.metric("年化收益率", f"{metrics['annual_return']:.2%}")
                c3.metric("最大回撤", f"{metrics['max_drawdown']:.2%}")
                c4.metric("夏普比率", f"{metrics['sharpe_ratio']:.2f}")

                # 绘制资金曲线
                fig = backtester.plot_results(metrics)
                st.plotly_chart(fig, use_container_width=True)
            else:
                st.error("回测失败，数据为空。")


if __name__ == "__main__":
    st.set_page_config(page_title="量化分析系统 Pro", layout="wide")
    main()