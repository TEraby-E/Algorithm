#include <iostream>
#include <string>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        string s;
        cin >> s;
        int energy = 0;
        int min = 0;

        for (char ch : s)
        {
            if (ch == 'c')
            {
                energy++;
            }
            if (ch == 'z')
            {
                energy--;
            }
            if (energy < min)
            {
                min = energy;
            }
        }
        if (min >= 0)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n"
                 << -min << '\n';
        }
    }
    return 0;
}
