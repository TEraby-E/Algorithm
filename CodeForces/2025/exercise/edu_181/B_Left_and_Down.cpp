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

u64 gcd(u64 a, u64 b){
    if(a < b)   swap(a,b);   
    while(b != 0){
        u64 tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}
void solve (){
    u64 x,y,k;
    cin >> x >> y >> k;
    if(k >= ( x > y ? x : y)) cout << "1" << endl;
    else{
        if((gcd(x,y) > 1 && ((( x > y ? x : y)/gcd(x,y)) > k))||gcd(x,y)==1)    cout << "2" << endl;
        else cout << "1" << endl;
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    u32 t; cin >> t;
    while (t--) solve();
    return 0;
}