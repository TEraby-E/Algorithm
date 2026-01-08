#include <bits/stdc++.h>

using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using u128 = unsigned __int128;

using a2 = array<int, 2>;
using a3 = array<int, 3>;
using a4 = array<int, 4>;

const int N = 1e6;
const int MAXN = 1e6 + 10;
const int inf = 1e9;
// const int mod = 1e9 + 7;
const int mod = 998244353;

void solve()
{
    long long a, b, cb;
    cin >> a >> b;
    if (a % 2 == 1 && b % 2 == 1)
    {
        cout << a * b + 1;
        return;
    }
    if (b % 2 == 1)
    {
        cout << "-1";
        return;
    }
    if (a * b / 2 % 2 == 1)
        cout << "-1";
    else
        cout << a * b / 2 + 2;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), std::cout.tie(0);
    u32 t;
    cin >> t;
    while (t--)
    {
        solve();
        std::cout << "\n";
    }
    return 0;
}