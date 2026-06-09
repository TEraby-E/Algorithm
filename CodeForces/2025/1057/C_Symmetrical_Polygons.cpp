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
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    map<int, int> cnt;
    for (auto num : a)
    {
        cnt[num]++;
    }
    int tmp = 0, ctl = 0;
    i64 sum = 0;
    vector<int> odd, even;
    for (auto [x, c] : cnt)
    {
        ctl++;
        sum += (i64)x * (c / 2);
        if (c % 2 == 1)
        {
            odd.push_back(x);
        }
        else if (c >= 2)
        {
            even.push_back(x);
        }
    }
    i64 ans = 0;
    for (int x : odd)
    {
        if (2 * sum > x)
        {
            ans = max(ans, 2 * sum + x);
        }
    }

    for (int i = 1; i < (int)odd.size(); i++)
    {
        if (odd[i - 1] + 2 * sum > odd[i])
        {
            ans = max(ans, odd[i - 1] + 2 * sum + odd[i]);
        }
    }

    for (int x : even)
    {
        if (sum - x > 0)
        {
            ans = max(ans, 2 * sum);
        }
    }
    cout << ans;
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
        cout << '\n';
    }
    return 0;
}