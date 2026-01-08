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
    cin >> n >> k;
    vector<i64> a(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    i64 cur = a[0], maxi = a[0];
    for (int i = 1; i < n; i++)
    {
        cur = max(a[i], cur + a[i]);
        maxi = max(maxi, cur);
    }
    if (k % 2 == 0)
    {
        cout << maxi;
        return;
    }
    vector<i64> L(n), R(n);
    cur = L[0] = a[0];
    for (int i = 1; i < n; i++)
    {
        cur = max(a[i], cur + a[i]);
        L[i] = cur;
    }
    cur = R[n - 1] = a[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        cur = max(a[i], cur + a[i]);
        R[i] = cur;
    }
    i64 ans = maxi;
    for (int i = 0; i < n; i++)
    {
        i64 val = L[i] + R[i] - a[i] + b[i];
        ans = max(ans, val);
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
        std::cout << "\n";
    }
    return 0;
}