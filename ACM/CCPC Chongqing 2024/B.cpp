#include <bits/stdc++.h>
using namespace std;
double round_n(double x, int n)
{
    double p = pow(10, n);
    return floor(x * p + 0.5) / p;
}
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int ppmax, a, b, c, d, e, f;
        double res = 0;

        cin >> ppmax >> a >> b >> c >> d >> e >> f;
        res = (300 * (a + b) + 200 * c + 100 * d + 50 * e) / double(3 * (a + b + c + d + e + f));
        double res2 = 5 * ppmax * max(((320 * a + 300 * b + 200 * c + 100 * d + 50 * e) / double(320 * (a + b + c + d + e + f)) - 0.8), 0.00);
        printf("%.2lf%% ", round_n(res, 2));
        printf("%.0lf\n", round_n(res2, 1));
    }
    return 0;
}