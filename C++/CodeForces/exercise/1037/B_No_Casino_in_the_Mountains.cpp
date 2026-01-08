#include <bits/stdc++.h>

using namespace std;
 
#define SPACE ' '
#define endl '\n'
 
using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
 
void solve (){
    u32 n, k, j = 1, ans = 0;
    cin >> n >> k;
    bool a[n + 5];
    int cnt[n + 5] = {0};

    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        if(!a[i]){
            cnt[j] ++;
        }
        else    j ++;
    }
    
    for(int i = 1; i <= min(j,n); i ++){
        ans += ((cnt[i] - (cnt[i] / (k+1))) / k) ;
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    u32 t; cin >> t;
    while (t--) solve();
    return 0;
}