#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using ll = long long;

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        ll w;
        cin >> n >> w;

        vector<ll> p(n), k(n);
        for (int i = 0; i < n; ++i)
            cin >> p[i];
        for (int i = 0; i < n; ++i)
            cin >> k[i];

        ll t = 0;
        ll cost = 0;

        for (int i = 0; i < n - 1; ++i)
        {
            ll need = p[i] / w;
            if (t > need)
            {
                p[i] -= need * w;
                t -= need;
            }
            else if (t >= 0)
            {
                p[i] -= need * w;
                t -= need;
            }
            cost += p[i];
            t += k[i];
            if (p[n - 1] > t * w)
                cost += p[n - 1] - t * w;
        }
        cout << cost << '\n';
    }
    return 0;
}