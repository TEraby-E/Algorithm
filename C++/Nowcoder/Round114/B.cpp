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
    cin >> n;
    map<char, int> s;
    for (int i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        s[c]++;
    }
    int min = inf;
    for (auto [x, c] : s)
    {

        if (c < min)
            min = c;
    }
    cout << (1 << min) - 1;
}

signed main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0), std::cout.tie(0);
    u32 t = 1;
    while (t--)
    {
        solve();
        std::cout << "\n";
    }
    return 0;
}