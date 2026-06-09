#include <bits/stdc++.h>

using namespace std;
 
#define SPACE ' '
#define endl '\n'
 
using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
 
void solve (){
    u32 n, c;
    i32 cmt = 0;
    cin >> n >> c;
    i32 a[n], res[n];
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        if(c >= a[i])
            res[i] = log2(c/(a[i]));
        else    res[i] = -1;
    }
    sort(res+1,res+n+1);
    for(int i = 1; i <= n; i ++){
        if(res[i]>=cmt){
            cmt ++;
        }
    }
    cout << n - cmt;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    u32 t; cin >> t;
    while (t--){
        solve();
        cout << endl;
    }
    return 0;
}