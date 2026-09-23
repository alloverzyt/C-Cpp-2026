#include<bits/stdc++.h>
#include<windows.h>
#include<iomanip>
using namespace std;
//string a=' ';
int main(){
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
	int w=info.srWindow.Right-info.srWindow.Left+1;
	int t=1,foreward=1;
	while(true){
		for(int i=1;i<=t;i++){
			cout<<" ";
		}
		cout<<"a"<<flush;
		Sleep(100);
		system("cls");
		if(foreward) t++;
		else t--;
		if(t+1>=w) foreward=0;
		if(t==0) foreward=1;
	}
	return 0;
}
