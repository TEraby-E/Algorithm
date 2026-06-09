#include <iostream>
using namespace std;

int ask(int i) {
    cout << "? " << i << endl;
    cout.flush();
    int res;
    cin >> res;
    return res;
}

void ans(int i) {
    cout << "! " << i << endl;
    cout.flush();
}

int main() {
    int n;
    cin >> n;

    int l = 1, r = n;

    while (l <= r) {
        int mid = (l + r) / 2;
        
        int a = ask(mid);
        if(r == l + 1){
            ans(mid);
            break;
        }
        if (a == 1) {
            r = mid;
        } 
        if (a == 0) {
            l = mid;
        }
    }
    return 0;
}