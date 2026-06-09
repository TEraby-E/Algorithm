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
    int n;
    cin >> n;
    int l = 1, r = n - 1;
    vector<int> a(n);
    vector<int> s(n + 1);
    for (auto &i : a)
    {
        cin >> i;
    }
    s[1] = a[0];
    for (int i = 2; i <= n; i++)
    {
        s[i] = s[i - 1] + a[i - 1];
    }
    for (; l <= r; l++, r--)
    {
        if (s[l] % 3 == (s[n] - s[r]) % 3 && s[l] % 3 == (s[r] - s[l]) % 3)
        {
            cout << l << " " << r;
            return;
        }
        if (s[l] % 3 != (s[n] - s[r]) % 3 && s[l] % 3 != (s[r] - s[l]) % 3 && (s[n] - s[r]) % 3 != (s[r] - s[l]) % 3)
        {
            cout << l << " " << r;
            return;
        }
        else
            cout << "0 0";
        return;
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