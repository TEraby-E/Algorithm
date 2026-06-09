#include <iostream>
#include <algorithm>
using namespace std;

#define pb push_back
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
const int mod = 998244353;

void solve()
{
    int n;
    cin >> n;
    int a[n + 1];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a, a + n);
    int l = unique((a + 1, a + n + 1) - a - 1);
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