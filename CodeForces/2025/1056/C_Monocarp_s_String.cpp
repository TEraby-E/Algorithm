#include <bits/stdc++.h>

#define pb push_back
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

using pii = std::pair<int, int>;
using a3 = std::array<int, 3>;
using a2 = std::array<int, 2>;
using a4 = std::array<int, 4>;

const int N = 1e6;
const int MAXN = 1e6 + 10;
const int inf = 1e9;
const int mod = 998244353;

void solve()
{

    int n;
    std::string s;
    std::cin >> n >> s;

    int a = count(s.begin(), s.end(), 'a');
    int b = n - a;
    int di = a - b;

    if (di == 0)
    {
        std::cout << 0;
        return;
    }

    std::unordered_map<int, int> cmp;
    cmp.reserve(n * 2);
    cmp[0] = 0;

    int pre = 0;
    int ans = inf;

    for (int i = 1; i <= n; ++i)
    {
        pre += (s[i - 1] == 'a' ? 1 : -1);
        int target = pre - di;

        if (cmp.count(target))
        {
            ans = std::min(ans, i - cmp[target]);
        }
        if (!cmp.count(pre))
            cmp[pre] = i;
    }

    if (ans == n || ans == inf)
        std::cout << -1;
    else
        std::cout << ans;
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0), std::cout.tie(0);
    u32 t;
    std::cin >> t;
    while (t--)
    {
        solve();
        std::cout << "\n";
    }
    return 0;
}