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
    std::string s;  std::cin >> s;
    int n = s.size();
    if (n & 1) {
        std::cout << "NO";
        return;
    }
    s = " " + s;
    for (int i = 2;i <= n - 2;i += 2)
    {
        int j = n - i;
        if ((s.substr(1, i / 2) == s.substr(1 + i / 2, i / 2)) && (s.substr(1 + i, j / 2) == s.substr(i + j / 2 + 1, j / 2))) {
            std::cout << "YES";
            return;
        }
    }
    std::cout << "NO";
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int t = 1;
    std::cin >> t;
    while (t--) {
        solve();
        std::cout << '\n';
    }
}