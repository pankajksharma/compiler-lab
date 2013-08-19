#include<fstream>
#include<iostream>
#include<string>
#include<algorithm>

/*
Asumptions:
I. States start from Q0.
II. Stated are in continuous fashion like Q0,1,2....
III. Q0 is initial and the state appearing at last is the final state.
*/

using namespace std;
class State{
	int inpc,inpsc[10],tstates[10][10];
	char inps[10], *name;
	public:
		State(){
			inpc=0;
			for(int i=0;i<10;i++)
				inpsc[i] = -1;
		}
		State(char* n){
			State();
			name = n;
		}
		State(int n){
			State();
			name = new char[2];
			name[0]=n;
			name[1]='\0';
		}
		void setNewTransition(char in, int a, int b, int t){
			inps[a] = in;
			tstates[a][b] = t;
			inpc = a;
			inpsc[a] = b;
		}
		char* getStateNum(){
			return name;
		}
		int getTransition(char inp){
			for(int i=0;i<inpc;i++){
				if(inps[i] == inp)
					return tstates[i][0];
			}			
			return -1;
		}
		void getAllTransitions(){
			cout<<"\nQ"<<name;
			for(int i=0;i<=inpc;i++){
				if(inps[i]!=NULL){
				cout<<"\n"<<inps[i]<<"=> ";
				for(int j=0;j<=inpsc[i];j++)
					cout<<" Q"<<tstates[i][j];
			}}		
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
	fstream f("NFA2DFA.TXT", ios::in);
	f.getline(temp,20,'\n');
	inps = getInputs(temp);
	while(f.getline(s[i++],20,'\n'));

	for(int j=0;j<i-1;j++)
		states[j] = new State((int)s[j][0]);
	
	for(int j=0;j<i-1;j++){
		int cti = 0, cc=0;
		for(int k=2;s[j][k]!='\0';k+=1)
			if(s[j][k] == ' '){
				cti++;
				cc = 0;
			}
			else if(s[j][k]>=48&&s[j][k]<=51)
				states[j]->setNewTransition(inps[cti], cti, cc++, (int)s[j][k]-48);
		states[j]->getAllTransitions();
	}
	cout<<"\n\nEnter String using \""<<inps<<"\": ";
	cin>>temp;
	int presentState = (int)states[0]->getStateNum(), istates[40],count=0;
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
