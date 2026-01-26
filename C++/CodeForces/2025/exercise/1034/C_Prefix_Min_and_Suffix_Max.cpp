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
    u32 n; 
    cin >> n;
    vector<u32> a(n);
    for (u32 &i : a) cin >> i;
    vector<u32> pref(n, 0); 
    pref[0] = a[0];
    for (u32 i = 1; i < n; i++) 
        pref[i] = min(pref[i - 1], a[i]);
    vector<u32> suf(n, 0); 
    suf[n - 1] = a[n - 1];
    for (u32 i = n - 2; i >= 1; i--) 
        suf[i] = max(suf[i + 1], a[i]);
    for (u32 i = 0; i < n; i++) {
        if (pref[i] <= a[i] && suf[i] <= a[i] ||
            pref[i] >= a[i] && suf[i] >= a[i]) cout << 1;
        else cout << 0;
    }
    cout << endl;
    return;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    u32 t; cin >> t;
    while (t--) solve();
    return 0;
}