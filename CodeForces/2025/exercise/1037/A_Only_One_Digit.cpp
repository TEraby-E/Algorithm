#include <bits/stdc++.h>
using namespace std;
 
#define SPACE ' '
#define endl '\n'
 
using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
 
void solve (){
    u32 x, y=(1 >> 31) - 1;
    cin >> x;
    while(x){
        int cnt = x % 10;
        x/=10;
        if(y > cnt) y = cnt;
    }
    cout << y << endl;

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    u32 t; cin >> t;
    while (t--) solve();
    return 0;
}