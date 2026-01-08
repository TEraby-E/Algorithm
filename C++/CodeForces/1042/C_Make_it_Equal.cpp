#include <bits/stdc++.h>

using namespace std;
#define ranges ranges
#define views views

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
    int n, k, sum = 0;
    cin >> n >> k;
    int s[n + 1], t[n + 1];
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
        s[i] %= k;
        if (s[i] > (k / 2))
            s[i] = k - s[i];
    }
    sort(s + 1, s + n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> t[i];
        t[i] %= k;
        if (t[i] > (k / 2))
            t[i] = k - t[i];
    }
    sort(t + 1, t + n + 1);
    for (int i = 1; i <= n; i++)
    {
        if (t[i] != s[i])
        {
            cout << "NO";
            return;
        }
    }
    cout << "YES";
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