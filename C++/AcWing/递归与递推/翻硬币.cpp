#include <bits/stdc++.h>
using namespace std;

string s, s1;
int res;
void turn(int i)
{
    if (s[i] == '*')
        s[i] = 'o';
    else
        s[i] = '*';
}
int main()
{
    cin >> s >> s1;
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        if (s[i] != s1[i])
        {
            turn(i), turn(i + 1);
            res++;
        }
    }
    cout << res;
    return 0;
}