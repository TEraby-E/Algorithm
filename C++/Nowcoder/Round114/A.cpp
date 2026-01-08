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
    map<int, int> a;
    for (int i = 0; i < 3; i++)
    {
        int num;
        cin >> num;
        a[num] += i + 1;
    }
    for (auto [x, c] : a)
    {
        cout << c << " ";
    }
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