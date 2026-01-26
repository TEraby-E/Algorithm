#include<bits/stdc++.h>
using namespace std;
 
#define SPACE ' '
#define endl '\n'
 
using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

void solve (){
    i32 a, b, x, y;
    cin >> a >> b >> x >> y;
    if (a > b)  cout << (((a ^ 1) == b) ? y : -1);
    else{
        int c0 = b - a;
        int c1 = (b + 1 >> 1) - (a + 1 >> 1);
        cout << 1ll * (c0 - c1) * x + 1ll * c1 * min(x, y);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    u32 t; cin >> t;
    while (t--){
        solve();
        cout << "\n";
    };
    return 0;
}