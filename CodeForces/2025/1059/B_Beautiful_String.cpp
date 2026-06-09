#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> pos;
    for (int i = 0; i < n; i++)
        if (s[i] == '0')
            pos.push_back(i + 1);

    cout << (int)pos.size() << '\n';
    for (auto &z : pos)
        cout << z << ' ';
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
        cout << '\n';
    }
    return 0;
}