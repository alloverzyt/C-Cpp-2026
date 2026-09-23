#include<bits/stdc++.h>
#include<windows.h>
#include<iomanip>
using namespace std;
//string a=' ';
int main(){
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
	int w=info.srWindow.Right-info.srWindow.Left+1;
	CONSOLE_CURSOR_INFO info_cursor;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info_cursor);
	info_cursor.bVisible=false;
	SetConsoleCursorInfo(GetStdHandle((STD_OUTPUT_HANDLE)),&info_cursor);
	int t=1,foreward=1;
	while(true){
		for(int i=1;i<=t;i++){
			cout<<" ";
		}
		cout<<"a"<<flush;
		Sleep(60);
		system("cls");
		if(foreward) t++;
		else t--;
		if(t+1>=w) foreward=0;
		if(t==0) foreward=1;
	}
	return 0;
}
