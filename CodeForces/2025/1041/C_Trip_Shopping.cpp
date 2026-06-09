#include <bits/stdc++.h>

using namespace std;
#define x first
#define y second

using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using u128 = unsigned __int128;

using pii = pair<int, int>;
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
    int n, k;
    cin >> n >> k;
    vector<pii> a(n + 1);
    i64 ans = 0;
    for (int i = 1; i <= n; i++)
        cin >> a[i].x;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i].y;
        if (a[i].x > a[i].y)
            swap(a[i].x, a[i].y);
        ans += abs(a[i].x - a[i].y);
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    u32 t;
    cin >> t;
    while (t--)
    {
        solve();
        cout << "\n";
    }
    return 0;
}