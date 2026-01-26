#include <bits/stdc++.h>
using namespace std;

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using u128 = unsigned __int128;

const int N = 1e6;
const int MAXN = 1e6 + 10;
const int inf = 1e9;
// const int mod = 1e9 + 7;
const int mod = 998244353;

void solve()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    set<int> s(v.begin(), v.end());
    s.erase(-1);
    if (s.size() <= 1 && !s.count(0))
        cout << "YES";
    else
        cout << "NO";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    u32 t;
    std::cin >> t;
    while (t--)
    {
        solve();
        cout << "\n";
    }
    return 0;
}