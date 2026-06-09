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
    int n, k;
    cin >> n >> k;
    if (k % 2 == 1)
    {
        for (int i = 0; i < k; i++)
        {
            cout << n << " ";
        }
    }
    else
    {
        vector<int> nums;
        for (int i = __lg(n); i >= 0; --i)
        {
            int sz = nums.size();
            if (n >> i & 1)
            {
                if (sz < k)
                {
                    nums.push_back(n ^ 1 << i);
                }
                else
                {
                    nums.back() ^= 1 << i;
                }
            }
            else
            {
                for (int j = 1; j < sz; j += 2)
                {
                    nums[j - 1] ^= 1 << i;
                    nums[j] ^= 1 << i;
                }
            }
        }
        for (int i = 0; i < k; ++i)
        {
            if (i < nums.size())
                cout << nums[i] << " ";
            else
                cout << n << ' ';
        }
    }
    return;
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
