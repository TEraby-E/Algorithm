#include <bits/stdc++.h>
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
    int n, k;
    cin >> n >> k;
    string s;
    std::cin >> s;
    vector<char> a(n + 1, '+');
    int i = 1, j = n;
    int cnt = 0;
    for (auto x : s)
    {
        if (x == '0')
            a[i] = '-', i++;
        if (x == '1')
            a[j] = '-', j--;
        if (x == '2')
            cnt++;
    }
    if (cnt == j - i + 1)
        for (; i <= j; i++)
            a[i] = '-';
    else
    {
        for (int t = 1; t <= cnt; t++)
            a[j - t + 1] = a[i + t - 1] = '?';
    }
    for (int i = 1; i <= n; i++)
        cout << a[i];
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