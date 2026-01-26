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
bitset<MAXN> vis;

void solve()
{
    int n;
    cin >> n;
    vector<vector<u32>> adj(n);
    for (int i = 1; i < n; i++)
    {
        int u, v, x, y;
        cin >> u >> v >> x >> y;
        u--, v--;
        if (x > y)
        {
            adj[u].push_back(v);
        }
        else
        {
            adj[v].push_back(u);
        }
    }
    vector<u32> order;
    order.reserve(n);
    auto dfs = [&](this auto &&dfs, u32 u) -> void
    {
        vis[u] = true;
        for (u32 v : adj[u])
            if (!vis[v])
                dfs(v);
        order.push_back(u);
    };
    vis.reset();
    for (u32 i = 0; i < n; i++)
        if (!vis[i])
            dfs(i);
    // reverse(order.begin(), order.end());
    vector<u32> ans(n);
    for (u32 i = 0; i < n; i++)
        ans[order[i]] = i + 1;
    for (u32 x : ans)
        cout << x << " ";
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