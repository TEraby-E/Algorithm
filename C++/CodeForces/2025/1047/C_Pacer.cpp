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
    bool tmp = 0;
    int n, m, res = 0;
    cin >> n >> m;
    res = m;
    int a[n], b[n];
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> b[i];
    }
    for (int i = 1; i <= n; i++)
    {
        if (!(a[i] % 2) && b[i] % 2 && !tmp)
        {
            tmp = 1;
            m--;
        }
        if (!(b[i] % 2) && a[i] % 2 && !tmp)
        {
            tmp = 1;
            m--;
        }

        if (a[i] % 2 && b[i] % 2 && tmp)
        {
            tmp = 0;
            m--;
        }

        if (!(b[i] % 2) && (!(a[i] % 2) && tmp))
        {
            tmp = 0;
            m--;
        }
    }
    cout << m;
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