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
    int m = 2 * n;
    vector<int> a(m);
    for (int i = 0; i < m; i++)
        cin >> a[i];

    map<int, int> cnt;
    for (int x : a)
        cnt[x]++;

    int cnto = 0;
    vector<int> costs;
    for (auto &p : cnt)
    {
        int c = p.second;
        if (c % 2 == 1)
        {
            cnto++;
        }
        else
        {
            int L = max(1, c - n);
            int R = min(n, c - 1);
            if (L <= R)
            {
                int x = (L % 2 == 1) ? L : L + 1;
                if (x <= R)
                    costs.push_back(x);
            }
        }
    }

    sort(costs.begin(), costs.end());
    int kmax = (int)costs.size();
    vector<int> pref(kmax + 1, 0);
    for (int i = 0; i < kmax; i++)
        pref[i + 1] = pref[i] + costs[i];

    int bestK = 0;
    for (int k = kmax; k >= 0; --k)
    {
        int s = pref[k];
        if (s > n)
            continue;
        if ((s % 2) == (n % 2))
        {
            bestK = k;
            break;
        }
        if (cnto > 0 && s <= n - 1)
        {
            bestK = k;
            break;
        }
    }

    int ans = cnto + 2 * bestK;
    cout << ans;
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