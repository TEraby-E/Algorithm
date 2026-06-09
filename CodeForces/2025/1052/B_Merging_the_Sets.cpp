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
    int n, m, sum = 0, max = 0;
    bool cor = 0;
    cin >> n >> m;
    vector<int> l(m + 1);
    set<int> cnt;
    for (int i = 1; i <= n; i++)
    {
        int ls;
        cin >> ls;
        if (ls > max)
            max = ls;
        for (int i = 1; i <= ls; i++)
        {
            cin >> l[i];
            cnt.insert(l[i]);
        }
        cout << cnt.size();
        if (cnt.size() == m)
            cor = 1;
        sum += ls;
    }

    if (sum >= m + 2 && n >= 3 && cor && sum >= 2 * max)
        cout << "YES";
    else
        cout << "NO";
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