#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define nf endl
#define ll long long
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
    string s;
    cin >> s;
    int sum1 = 0, sum2 = 0;
    int cnt1 = 0, cnt2 = 0;
    int res1 = 0, res2 = 0;
    vector<int> a;
    vector<int> b;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'a')
            a.push_back(i + 1);
        if (s[i] == 'b')
            b.push_back(i + 1);
    }
    int m = a.size();
    int h = b.size();
    for (int i = 0; i < m; i++)
    {
        sum1 += a[i];
    }
    for (int i = 0; i < h; i++)
    {
        sum2 += b[i];
    }
    int a1 = sum1 / m;
    int a2 = sum2 / h;
    for (int i = 0; i < m; i++)
    {
        if (a[i] <= a1)
            cnt1++;
    }
    int ccnt1 = cnt1 * (cnt1 + 1) / 2;
    for (int i = 0; i < h; i++)
    {
        if (b[i] <= a2)
            cnt2++;
    }
    int ccnt2 = cnt2 * (cnt2 + 1) / 2;
    for (int i = 0; i < m; i++)
    {
        res1 += abs(a1 - a[i]);
    }
    res1 -= ccnt1;
    res1 += m;
    res1 -= cnt1;
    for (int i = 0; i < h; i++)
    {
        res2 += abs(a2 - b[i]);
    }
    res2 -= ccnt2;
    res2 += h;
    res2 -= cnt2;
    cout << min(res1, res2);
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