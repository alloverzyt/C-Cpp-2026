#include <stdio.h>
#include<bits/stdc++.h>
using namespace std;
int main() {
    while(true){
    int n;bool c=0;
    cin>>n;
	if(n==1){
		cout<<"NO"<<endl;
		continue;
	}
    for(int i=2;i<=sqrt(n);i++){
        if(n%i==0){
            c=1;
        }
    }
    if(!c) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
    }
    return 0;
}
