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
int cmp(int a, int b)
{
    return a > b;
}
void solve()
{
    int n, min = MAXN, tmp = 0;
    cin >> n;
    int max = 0;
    int a[n + 1], cnt[n + 1] = {0};
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        cnt[a[i]]++;
    }
    sort(cnt + 1, cnt + n + 1, cmp);

    for (int i = 1; i <= n; i++)
    {
        if (cnt[i] != 0)
        {
            tmp++;
        }
        if ((cnt[i] <= min) && cnt[i] != 0)
        {
            min = cnt[i];
        }
        if (min * tmp >= max && cnt[i] != 0)
            max = min * tmp;
    }
    cout << max;
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