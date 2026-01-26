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
    int n;
    cin >> n;
    vector<a3> edges(n);
    for (auto &[x, y, id] : edges)
        cin >> x >> y;
    for (int i = 0; i < n; i++)
    {
        edges[i][2] = i;
    }
    ranges::sort(edges);
    int last = 0;
    vector<int> ans;
    for (auto &[x, y, id] : edges)
    {
        if (y >= last)
        {
            ans.push_back(id);
            last = y + 1;
        }
    }
    cout << ans.size() << '\n';
    for (auto &x : ans)
        cout << x + 1 << ' ';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), std::cout.tie(0);
    u32 t;
    std::cin >> t;
    while (t--)
    {
        solve();
        std::cout << '\n';
    }
    return 0;
}