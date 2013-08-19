#include<iostream>
#include<fstream>
using namespace std;
int main(){
	char s[80];
	ifstream f("INP.TXT", ios::in);
	if(f!=NULL)
		cout<<"Hello World\n";
	istream *is = f.getline(s, 80, '\n');
	f.clear();
	cout<<s;
	return 1;
}
