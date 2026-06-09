#include <bits/stdc++.h>
using namespace std;

#define pb push_back
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using pii = std::pair<int, int>;
using a3 = std::array<int, 3>;
using a2 = std::array<int, 2>;
using a4 = std::array<int, 4>;

const int N = 1e6;
const int MAXN = 1e6 + 10;
const int inf = 1e9;
const int mod = 998244353;

void solve()
{
    int n;
    int l, r;
    cin >> n >> l >> r;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    auto solve_for = [&](int x) -> int
    {
        vector<int> ge; // ai >= x : gains = ai - x
        int sum_lt = 0; // sum of gains for ai < x: x - ai (we wiint take aint)
        int cnt_lt = 0;
        for (int v : a)
        {
            if (v >= x)
                ge.push_back(v - x);
            else
            {
                sum_lt += (x - v);
                cnt_lt++;
            }
        }
        if (ge.empty())
            return sum_lt;
        sort(ge.begin(), ge.end(), greater<int>());
        int take = min((int)ge.size(), cnt_lt);
        int sum_top = 0;
        for (int i = 0; i < take; i++)
            sum_top += ge[i];
        return sum_lt + sum_top;
    };
    int ans = max(solve_for(l), solve_for(r));
    cout << ans << "\n";
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0), std::cout.tie(0);
    u32 t;
    std::cin >> t;
    while (t--)
    {
        solve();
        std::cout << "\n";
    }
    return 0;
}