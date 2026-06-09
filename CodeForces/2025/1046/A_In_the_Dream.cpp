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
    const int LIMIT = 100; // 限制 a,b 最大值

    queue<pair<int, int>> q;
    set<pair<int, int>> visited;

    q.push({0, 0});
    visited.insert({0, 0});

    while (!q.empty())
    {
        auto [a, b] = q.front();
        q.pop();

        // 扩展下一步
        for (int da = 0; da <= 2; da++)
        {
            for (int db = 0; db <= 2; db++)
            {
                if (da == 0 && db == 0)
                    continue; // 不能原地不动

                int na = a + da;
                int nb = b + db;

                if (na <= LIMIT && nb <= LIMIT && !visited.count({na, nb}))
                {
                    visited.insert({na, nb});
                    q.push({na, nb});
                }
            }
        }
    }
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