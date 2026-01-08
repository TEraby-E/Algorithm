#include <bits/stdc++.h>
using namespace std;

#define pb push_back
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using pii = pair<int, int>;
using a3 = array<int, 3>;
using a2 = array<int, 2>;
using a4 = array<int, 4>;

const int N = 1e6;
const int MAXN = 1e6 + 10;
const int inf = 1e9;
const int mod = 998244353;

void solve()
{
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<int> a(m + 1);
    for (int i = 1; i <= m; i++)
        cin >> a[i];
    int f = 0;
    for (auto x : s)
        if (x == 'B')
            f = 1;
    if (!f)
    {
        for (int i = 1; i <= m; i++)
            cout << a[i] << '\n';
    }
    else
    {
        for (int i = 1; i <= m; i++)
        {
            int j = 0, ans = 0;
            while (1)
            {
                if (s[j] == 'A')
                    a[i]--;
                else
                    a[i] /= 2;
                j++;
                if (j == n)
                    j = 0;
                ans++;
                if (!a[i])
                {
                    cout << ans << '\n';
                    break;
                }
            }
        }
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
    }
    return 0;
}