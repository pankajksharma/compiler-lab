#include<fstream>
#include<iostream>
#include<string.h>

/*
Asumptions:
I. States start from Q0.
II. Stated are in continuous fashion like Q0,1,2....
II. Q0 is initial and the state appearing at last is the final state.
*/

using namespace std;
class State{
	int num,inpc,tstates[10];
	char inps[10];
	public:
		State(){
			inpc=0;
		}
		State(int n){
			State();
			num = n;
		}
		void setNewTransition(char in, int t){
			inps[inpc] = in;
			tstates[inpc++] = t;
		}
		int getStateNum(){
			return num;
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
};


char* getInputs(char *s){
	char *inps = new char[10];
	int count=0;
	for(int i=0;s[i]!='\0';i++)
		if(s[i-1]==' ' && s[i]!=' ' &&(s[i+1]==' '||s[i+1]=='\0'))
			inps[count++]=s[i];
	return inps;
}

int main(){
	int ic,i=0;
	char s[20][20],temp[40],c, *inps;
	State *states[10];
	fstream f("NFA.TXT", ios::in);
	f.getline(temp,20,'\n');
	inps = getInputs(temp);
	while(f.getline(s[i++],20,'\n'))
	{
		cout<<s[i-1]<<"\n";
	}
	for(int j=0;j<i-1;j++)
		states[j] = new State((int)s[j][0]-48);
	
	for(int j=0;j<i-1;j++){
		for(int k=2;s[j][k]!='\0';k+=1)
			if(s[j][k]>=48&&s[j][k]<=51)
				states[j]->setNewTransition(inps[(k-2)/2], (int)(s[j][k]-48));
		states[j]->getAllTransitions();
	}
	cout<<"\n\nEnter String using \""<<inps<<"\": ";
	cin>>temp;
	int presentState = states[0]->getStateNum(), istates[40],count=0;
	istates[count++] = presentState;
	for(int j=0;temp[j]!='\0';j++){
		presentState = states[presentState]->getTransition(temp[j]);		
		if(presentState == -1){
			cout<<"Given input doesn't belong to given NFA.\n";
			return 1;		
		}
		istates[count++] = presentState;
	}
	if(presentState == i-2){
		cout<<"Given input is correct.\nTransition would be as follow:\nQ"<<istates[0];
		for(i=1;i<count;i++)
			cout<<" -> Q"<<istates[i];
		cout<<"\n";
	}	
	else
		cout<<"Given input doesn't belong to given NFA.\n";
}
