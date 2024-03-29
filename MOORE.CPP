#include<fstream>
#include<iostream>
#include<string.h>

using namespace std;
class State{
	int num,inpc,tstates[10],id;
	char inps[10],out;
	public:
		State(){
			inpc=0;
		}
		State(int n, int i){
			State();
			num = n;
			id = i;
		}
		void setOutput(char o){
			out=o;
		}
		void setNewTransition(char in, int t){
			inps[inpc] = in;
			tstates[inpc++] = t;
		}
		int getStateNum(){
			return num;
		}
		int getStateId(){
			return id;
		}
		int getTransition(char inp){
			for(int i=0;i<inpc;i++){
				if(inps[i] == inp)
					return tstates[i];
			}			
			return -1;
		}
		void getAllTransitions(){
			cout<<"\nQ"<<num;
			for(int i=0;i<inpc;i++)
				cout<<"\n"<<inps[i]<<" Q"<<tstates[i];
		}
		char getOutput(){
			return out;
		}
};


char* getInputs(char *s){
	char *inps = new char[10];
	int count=0;
	for(int i=0;s[i]!='\0';i++)
		if(s[i-1]==' ' && s[i]!=' ' &&s[i+1]==' ')
			inps[count++]=s[i];
	return inps;
}

int main(){
	int ic,i=0;
	char s[20][20],temp[40],c, *inps;
	State *states[10];
	fstream f("INP.TXT", ios::in);
	f.getline(temp,20,'\r');
	f.get(c);
	inps = getInputs(temp);
	while(f.getline(s[i++],20,'\r'))
	{
		f.get(c);
	}
	for(int j=0;j<i-1;j++)
		states[j] = new State((int)s[j][0]-48, j);
	
	for(int j=0;j<i-1;j++){
		for(int k=2;s[j][k]!='\0';k+=1)
			if(k==strlen(s[j])-1)
				states[j]->setOutput(s[j][k]);
			else if(s[j][k]>=48&&s[j][k]<=51)
				states[j]->setNewTransition(inps[(k-2)/2], (int)(s[j][k]-48));
		states[j]->getAllTransitions();
	}
	cout<<"\n\nEnter String using \""<<inps<<"\": ";
	cin>>temp;
	int presentState = states[0]->getStateId(), oCount=0;
	//cout<<presentState;
	char *out = new char[40];
	out[oCount++] = states[presentState]->getOutput();
	for(int j=0;temp[j]!='\0';j++){
		presentState = states[presentState]->getTransition(temp[j]);		
		if(presentState == -1){
			cout<<"Given input doesn't belong to given Moore machine.\n";
			return 1;
		}
		else{
			out[oCount++] = states[presentState]->getOutput();
		}
	}
	out[oCount]=0;
	if(presentState == i-2)
		cout<<"Output: "<<out<<"\n";
	else
		cout<<"Given input doesn't belong to given Moore machine.\n";
}
