#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
#define SPACE ' '
#define endl '\n'
 
using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
 
void solve (){
    u32 n, j, k;
    cin >> n >> j >> k;
    vector<u32> a(n);
    u32 b = 1;

    for(u32 &i : a)    cin >> i;
    for(u32 i : a)
    {
        if(a[j] < i)	b ++;
    } 
    cout << b;
    if(k >= 2 && k <= n || k == 1 && b == 1)    cout << "Yes";
    else    cout << "No"; 
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    u32 t; cin >> t;
    while (t--){
        solve();
        cout << endl;
    }
    return 0;
}