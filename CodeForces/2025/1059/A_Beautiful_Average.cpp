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
    int n, res = 0;
    cin >> n;
    vector<int> a(n);
    for (auto &i : a)
    {
        cin >> i;
    }
    sort(a.begin(), a.end());
    for (int i = a.size() - 1; i >= 0; i--)
    {
        int sum = 0;
        sum += a[i];
        sum /= n - i;
        if (sum > res)
            res = sum;
    }
    cout << res;
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