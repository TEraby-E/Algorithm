#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve()
{
    int n;
    cin >> n;

    vector<int>
        r(n);
    for (int i = 0; i < n; i++)
        cin >> r[i];

    if (n < 2)
    {
        cout << 0 << endl;
        return;
    }

    vector<int> d(n - 1);
    for (int i = 0; i < n - 1; i++)
    {
        d[i] = r[i + 1] - r[i];
    }

    int res = 0;

    for (int i = 0; i < n - 1; i++)
    {

        if (i == n - 2)
        {
            res++;
            break;
        }

        bool tmp = true;

        if (i + 1 < n - 1)
        {
            int left = d[i];
            int mid = d[i + 1];

            int right = (i + 2 < n - 1) ? d[i + 2] : 0;

            if (mid >= left + right && right > 0)
            {

                tmp = false;
            }
        }

        if (!tmp)
        {
            res++;
            i++;
        }
        else
        {
            res++;
        }
    }

    cout << res << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 0;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}