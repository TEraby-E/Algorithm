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
    int n, res = 0, tmp = 0;
    cin >> n;
    int p[n + 2];
    vector<int> p1(n);
    vector<int> t;
    vector<int> t1;
    vector<int> dif;
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
        if (p[i] != 0)
        {
            t.push_back(p[i]);
            t1.push_back(p[i]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        p1[i] = i + 1;
    }
    sort(t.begin(), t.end());
    set_difference(p1.begin(), p1.end(), t.begin(), t.end(), back_inserter(dif));
    for (int i = 0, j = dif.size() - 1; i < n; i++)
    {
        if (p[i] == 0)
        {
            p[i] = dif[j];
            j--;
            tmp++;
        }
    }
    for (int i = 0; i < p1.size(); i++)
    {
        if (p[i] != p1[i])
            res++;
    }
    if (tmp != 1)
        cout << max(res, tmp);
    else
        cout << res;
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