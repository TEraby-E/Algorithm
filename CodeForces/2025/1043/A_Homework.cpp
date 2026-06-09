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
    string a, b, c;
    int n, m;
    cin >> n >> a;
    cin >> m >> b >> c;
    string add_left = "";
    for (int i = 0; i < m; ++i)
    {
        if (c[i] == 'V')
        {
            add_left += b[i];
        }
        else
        {
            a += b[i];
        }
    }
    reverse(add_left.begin(), add_left.end());
    cout << add_left + a;
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