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
    int n, k;
    int res1 = 0;
    cin >> n >> k;
    string s;
    bool cmp = 0;
    cin >> s;
    vector<int> res;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '1' && !cmp)
        {
            res1++;
            cmp = 1;
            res.push_back(1 + i);
        }
        if (s[i] == '1' && cmp)
        {
            res.push_back(1 + i);
        }
    }

    int m = res.size();
    vector<int> re(m);
    for (int i = 1; i < m; i++)
    {
        re[i] = res[i] - res[i - 1];
    }
    for (auto &p : re)
    {

        if (p > k - 1)
            res1++;
    }
    cout << res1;
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