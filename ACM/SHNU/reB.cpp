#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+8;
int a[N], b[N];
int main(){
	int n,cnt,res=0;
    cin >> n;
    cnt = n;
    for(int i = 1; i <= n; i ++)
    {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i ++)
    {
        cin >> b[i];
    }
    for(int i = n; i >= 1; i --){
        if(a[cnt] > b[i]){
            cnt--;
            res++;
        }
    }
    cout << res;
    return 0;
}