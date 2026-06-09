#include <bits/stdc++.h>
using namespace std;

#define nl "\n"
#define nf endl
#define ll long long
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
// const int mod = 1e9 + 7;
const int mod = 998244353;

void solve()
{
    int n, k;
    int tmp1 = 0, tmp2 = 0;
    cin >> n >> k;
    vector<int> a(n);
    set<int> cnt;
    for (auto &i : a)
    {
        cin >> i;
        if (i < k)
            cnt.insert(i);
    }
    sort(a.begin(), a.end());
    for (auto &i : a)
    {
        if (i == k)
            tmp2++;
    }
    int h = cnt.size();
    cout << max(k - h, tmp2);
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