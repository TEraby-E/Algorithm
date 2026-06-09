#include <bits/stdc++.h>

using namespace std;
#define ranges ranges
#define views views

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
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];

    if (a[n] != b[n])
    {
        cout << "NO";
        return;
    }
    for (int i = n - 1; i >= 1; i--)
    {
        if (a[i] == b[i])
            continue;
        else
        {
            int num1 = a[i] ^ a[i + 1];
            int num2 = a[i] ^ b[i + 1];
            if (num1 != b[i] && num2 != b[i])
            {
                cout << "NO";
                return;
            }
        }
    }
    cout << "YES";
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