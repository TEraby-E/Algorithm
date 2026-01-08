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

i64 qpow(i64 x, i64 b) {
    i64 ret = 1;
    while (b) {
        if (b & 1) ret = ret * x % 10;
        b >>= 1;
        x = x * x % 10;
    }
    return ret;
}
std::vector<std::vector<int>> a(9);
void solve()
{
    i64 l, r;   std::cin >> l >> r;
    if (l == r) {
        std::cout << l % 10;
        return;
    }
    if (l % 10 == 0 || l % 10 == 1 || l % 10 == 5 || l % 10 == 6) {
        std::cout << l % 10;
        return;
    }

    a[2] = { 6,2,4,8 };
    a[3] = { 1,3,9,7 };
    a[7] = { 1,7,9,3 };
    a[8] = { 6,8,4,2 };
    int d = l % 10;
    if (d == 4) {
        std::cout << 4;
    }
    else if (d == 9) {
        std::cout << 1;
    }
    else {
        if (r == l + 1) {
            r %= 4;
            std::cout << a[d][r];
        }
        else {
            int p = 0;
            if ((l + 1) % 4 == 0) p = 0;
            if ((l + 1) % 4 == 1) p = 1;
            if ((l + 1) % 4 == 2) p = 0;
            if ((l + 1) % 4 == 3) {
                if ((l + 2) & 1) p = 3;
                else p = 1;
            }
            std::cout << a[d][p];
        }
    }
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