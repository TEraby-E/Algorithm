#include <bits/stdc++.h>

using namespace std;
 
#define SPACE ' '
#define endl '\n'
 
using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
 
void solve (){
    int n, m;   std::cin >> n >> m;
    if ((n >= 3 && m >= 2) || (n >= 2 && m >= 3))  std::cout << "YES\n";
    else std::cout << "NO\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    u32 t; cin >> t;
    while (t--){
        solve();
    }
    return 0;
}