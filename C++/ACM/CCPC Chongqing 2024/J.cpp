#include <iostream>
using namespace std;
int main()
{
    int a[5] = {6, 9, 10, 14};
    int b[5] = {6, 8, 9, 14};
    int n, m;
    cin >> n >> m;
    if (n >= 2 && m >= 2)
        cout << n * m * 6;
    else if (n == 1 && m != 1)
        cout << (m / 4) * 14 + a[m % 4 - 1];
    else if (m == 1 && n != 1)
        cout << (n / 4) * 14 + b[n % 4 - 1];
    else
        cout << 6;
}