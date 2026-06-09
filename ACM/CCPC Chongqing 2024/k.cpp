#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int n;
    cin >> n;
    string s1, s2;
    cin >> s1;
    cin >> s2;
    for (int i = 0; i < n; i++)
    {
        if ((s1[i] == '0' && s2[i] != '1') || (s1[i] == '2' && s2[i] != '1'))
        {
            cout << 0;
            return 0;
        }
    }
    cout << 1;
    return 0;
}