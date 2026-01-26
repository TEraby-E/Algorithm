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
 
void solve() {
    u32 n, k; cin >> n >> k;
    string s; cin >> s;
    u32 tmp = 0;
    for (char i : s) if (i == '1') tmp++;
    if (tmp <= k || n < k * 2) cout << "Alice" << endl;
    else cout << "Bob" << endl;
    return;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    u32 t; cin >> t;
    while (t--) solve();
    return 0;
}