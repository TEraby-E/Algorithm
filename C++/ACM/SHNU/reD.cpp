#include<bits/stdc++.h>
using namespace std;
int main(){
    for(int i = 1;i <= 8; i++){
        for(int j = 1; j <=8; j ++){
            if((i % 2 && j % 2) || (!(i % 2))&&(!(j % 2)))    cout << "H";
            else    cout << "N";
        }
        puts("");
    }    
    return 0;
}