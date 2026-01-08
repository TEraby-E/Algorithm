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
    bool temp = true;
    u64 n;
    vector<u64> res;
    cin >> n;

    for (int i = 18; i >= 1; i--)
    {
        u64 m = pow(10, i);
        if (!(n % (m + 1)))
        {
            res.push_back(n / (m + 1));
            temp = false;
        }
    }
    if (temp)
        cout << 0;
    else
    {
        cout << res.size() << endl;
        for (auto &i : res)
        {
            cout << i << " ";
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