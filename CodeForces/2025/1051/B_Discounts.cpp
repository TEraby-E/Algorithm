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
    vector<i64> a(n);
    vector<int> b(k);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int j = 0; j < k; j++)
        cin >> b[j];
    sort(a.begin(), a.end(), greater<i64>());
    sort(b.begin(), b.end());

    i64 cnt = accumulate(a.begin(), a.end(), 0LL);
    i64 res = 0;

    int idx = 0;
    for (int bj : b)
    {
        if (idx + bj - 1 < n)
        {
            res += a[idx + bj - 1];
            idx += bj;
        }
    }

    cout << cnt - res;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
    {
        solve();
        cout << "\n";
    }
    return 0;
}