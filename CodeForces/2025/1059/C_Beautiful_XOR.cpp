#include <iostream>
#include <bit>
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
    int a, b;
    cin >> a >> b;
    int x = a ^ b;
    if (a == b)
        cout << 0;
    else if (a < b)
    {

        if (x <= a)
        {
            cout << 1 << endl;
            cout << x;
        }
        else
        {
            cout << -1;
        }
    }

    else
    {

        if (x <= a)
        {
            cout << 1 << endl;
            cout << x;
        }
        else
        {
            cout << 2 << endl;
            cout << b << " " << a;
        }
    }
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