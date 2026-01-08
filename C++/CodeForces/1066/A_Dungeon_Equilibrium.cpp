#include <bits/stdc++.h>
using namespace std;

#define pb push_back
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using pii = std::pair<int, int>;
using a3 = std::array<int, 3>;
using a2 = std::array<int, 2>;
using a4 = std::array<int, 4>;

const int N = 1e6;
const int MAXN = 1e6 + 10;
const int inf = 1e9;
const int mod = 998244353;

void solve()
{
    int n;
    int sum = 0;
    cin >> n;
    vector<int> cnt(n + 1, 0);
    for (int i = 0; i < n; i++)
    {
        int c;
        cin >> c;
        cnt[c]++;
    }
    for (int i = 0; i <= n; i++)
    {
        if (cnt[i] < i)
            sum += cnt[i];
        else if (cnt[i] > i)
            sum += cnt[i] - i;
    }
    cout << sum;
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0), std::cout.tie(0);
    u32 t;
    std::cin >> t;
    while (t--)
    {
        solve();
        std::cout << "\n";
    }
    return 0;
}