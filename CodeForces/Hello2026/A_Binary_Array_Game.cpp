#include <bits/stdc++.h>

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
    std::cin >> n;
    std::vector<int> a(n+1);
    for(int i = 1; i <= n; i ++){
        std::cin >> a[i];
    }
    if(a[1]+a[n]==0){
        std::cout << "Bob";
    }
    else    std::cout << "Alice";
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