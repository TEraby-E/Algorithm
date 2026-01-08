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
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    int cmt[20] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int p = 0;
    for (int i = 0; i < 14; i++)
    {
        p = cmt[i];
        if (k % p != 0)
            break;
    }
    for (int i = 0; i < n; i++)
    {
        while (a[i] % p)
        {
            a[i] += k;
        }
        cout << a[i] << " ";
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