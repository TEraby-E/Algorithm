#include <bits/stdc++.h>

#define ranges std::ranges
#define views std::views

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

using pii = std::pair<int, int>;
using a3 = std::array<int, 3>;
using a4 = std::array<int, 4>;

const int dx[8] = { -1, 0, 1, 0, -1, -1, 1, 1 }, dy[8] = { 0, 1, 0, -1, -1, 1, -1, 1 };
const int N = 1e6;
const int MAXN = 1e6 + 10;
const int inf = 1e9;
const i64 INF = 1e18;
const int mod = 1e9 + 7;

void solve()
{
    int n, m, k;    std::cin >> n >> m >> k;
    int mn = inf, mx = 0;
    std::vector a(n + 1, std::vector<int>(m + 1));
    for (int i = 1;i <= n;i++)
        for (int j = 1;j <= m;j++)
        {
            std::cin >> a[i][j];
            mn = std::min(mn, a[i][j]);
            mx = std::max(mx, a[i][j]);
        }


    auto check = [&](int x) {
        std::vector dp(n + 1, std::vector<int>(m + 1, -inf));
        dp[1][1] = (a[1][1] > x ? k - 1 : k);
        for (int i = 1;i <= n;i++)
            for (int j = 1;j <= m;j++)
            {
                if (i != 1) dp[i][j] = std::max(dp[i][j], dp[i - 1][j] + (a[i][j] > x ? -1 : 0));
                if (j != 1) dp[i][j] = std::max(dp[i][j], dp[i][j - 1] + (a[i][j] > x ? -1 : 0));
            }
        return dp[n][m] >= 0;
        };

    int l = mn, r = mx;
    int ans = 0;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }

    std::cout << ans;
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int t = 1;
    //std::cin >> t;
    while (t--) {
        solve();
        std::cout << '\n';
    }
}