# modules/model_predictor.py

import pandas as pd
import numpy as np
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, classification_report
from sklearn.preprocessing import StandardScaler
import ta  # 技术指标库
import logging

logger = logging.getLogger("MarketPredictor")


class MarketPredictor:
    def __init__(self):
        self.model = RandomForestClassifier(n_estimators=100, random_state=42)
        self.scaler = StandardScaler()

    def feature_engineering(self, df: pd.DataFrame) -> pd.DataFrame:
        """生成技术指标特征"""
        if df.empty or len(df) < 30:
            return pd.DataFrame()

        df = df.copy()

        # 1. 移动平均线
        df['SMA_5'] = ta.trend.sma_indicator(df['close'], window=5)
        df['SMA_20'] = ta.trend.sma_indicator(df['close'], window=20)

        # 2. 相对强弱指标 (RSI)
        df['RSI'] = ta.momentum.rsi(df['close'], window=14)

        # 3. MACD
        macd = ta.trend.MACD(df['close'])
        df['MACD'] = macd.macd()
        df['MACD_signal'] = macd.macd_signal()

        # 4. 布林带
        bollinger = ta.volatility.BollingerBands(df['close'])
        df['BB_High'] = bollinger.bollinger_hband()
        df['BB_Low'] = bollinger.bollinger_lband()

        # 5. 涨跌幅特征
        df['pct_change'] = df['close'].pct_change()

        # 6. 目标变量 (Target): 明日是否上涨 (1=涨, 0=跌)
        df['Target'] = (df['close'].shift(-1) > df['close']).astype(int)

        return df.dropna()

    def train_and_evaluate(self, df: pd.DataFrame):
        """训练模型并返回评估结果"""
        data = self.feature_engineering(df)
        if data.empty:
            return None, None, "数据不足，无法训练"

        # 特征列
        feature_cols = ['SMA_5', 'SMA_20', 'RSI', 'MACD', 'MACD_signal', 'BB_High', 'BB_Low', 'pct_change']
        X = data[feature_cols]
        y = data['Target']

        # 划分训练集和测试集 (后20%作为测试)
        split_idx = int(len(data) * 0.8)
        X_train, X_test = X.iloc[:split_idx], X.iloc[split_idx:]
        y_train, y_test = y.iloc[:split_idx], y.iloc[split_idx:]

        # 数据标准化
        X_train_scaled = self.scaler.fit_transform(X_train)
        X_test_scaled = self.scaler.transform(X_test)

        # 训练模型
        self.model.fit(X_train_scaled, y_train)

        # 预测
        y_pred = self.model.predict(X_test_scaled)

        # 评估
        accuracy = accuracy_score(y_test, y_pred)
        report = classification_report(y_test, y_pred, output_dict=True)

        # 获取特征重要性
        importances = pd.DataFrame({
            'feature': feature_cols,
            'importance': self.model.feature_importances_
        }).sort_values(by='importance', ascending=False)

        return {
            "accuracy": accuracy,
            "report": report,
            "feature_importance": importances,
            "X_test": X_test,
            "y_test": y_test,
            "y_pred": y_pred
        }

    def predict_next_day(self, df: pd.DataFrame):
        """使用最新数据预测明日走势"""
        data = self.feature_engineering(df)
        if data.empty: return None

        # 取最后一行数据作为输入
        last_row = data.iloc[[-1]]
        feature_cols = ['SMA_5', 'SMA_20', 'RSI', 'MACD', 'MACD_signal', 'BB_High', 'BB_Low', 'pct_change']

        X_new = last_row[feature_cols]
        X_new_scaled = self.scaler.transform(X_new)

        prediction = self.model.predict(X_new_scaled)[0]
        prob = self.model.predict_proba(X_new_scaled)[0]

        return {
            "prediction": "上涨 📈" if prediction == 1 else "下跌 📉",
            "probability_up": prob[1],
            "probability_down": prob[0]
        }