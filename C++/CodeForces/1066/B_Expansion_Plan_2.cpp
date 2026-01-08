#include <bits/stdc++.h>
using namespace std;

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
    long long x, y;
    cin >> n >> x >> y;

    string s;
    cin >> s;

    int c4 = 0, c8 = 0;
    for (char c : s)
    {
        if (c == '4')
            c4++;
        else
            c8++;
    }

    long long absX = abs(x);
    long long absY = abs(y);
    long long dis1 = max(absX, absY);
    long long dis2 = absX + absY;
    long long minn = min(absX, absY);
    long long maxn = max(absX, absY);
    long long step = min((long long)c8, minn);
    long long rmax = maxn - step;
    long long rmin = minn - step;
    long long l8 = c8 - step;
    long long res = rmax + rmin - l8;

    if (res <= c4)
    {
        cout << "YES";
    }
    else
    {
        cout << "NO";
    }
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