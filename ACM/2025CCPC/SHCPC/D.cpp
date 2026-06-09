#include<bits/stdc++.h>
using namespace std;

int main(){
	int T;
    cin>>T;
	while(T--){
		long long a,b,x,y;
        cin>>a>>b>>x>>y;
		cout<<(((a&x)==x&&b==y)||(a==x&&(b|y)==y)?"Yes\n":"No\n");
	}
	return 0;
}