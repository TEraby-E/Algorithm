#include <bits/stdc++.h>

using namespace std;
 
#define SPACE ' '
#define endl '\n'
 
using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
 
void solve (){
    i32 n, x;
    cin >> n >> x;
    vector<int> a(n+1);
    i32 sum = 0;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        sum += a[i];
    }
    if (sum % x == 0 && sum / x == n)    cout << "YES\n";
    else cout << "NO\n";
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