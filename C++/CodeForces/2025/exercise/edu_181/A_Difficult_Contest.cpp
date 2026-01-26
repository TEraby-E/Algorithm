#include <bits/stdc++.h>
 
#define SPACE ' '
#define endl '\n'
using namespace std;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using u128 = unsigned __int128;

void solve() {
    string s;
    cin >> s;
    int n = s.length();
    for(int i = 0,j = 0; i < n; i ++){
        if(s[i]=='T'){
            swap (s[i],s[j]);
            j ++;
        }
    }
    cout << s;
}
 
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;std::cin >> t;
    while (t--) {
        solve();
        std::cout << '\n';
    }
    return 0;
}