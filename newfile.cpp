#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
int counter=0;
char table[9]={'1','2','3','4','5','6','7','8','9'};
string player1;
string player2;
struct scoreBoard{
	string name;
	int win,lose,draw;
};
scoreBoard S[10000];
void getName(){
	cout<<"Enter the name of the first player : ";
	cin>>player1;
	cout<<"Enter the name of the second player : ";
	cin>>player2;
	cout<<endl;
}
char X_or_O(int turn){
	if(turn % 2 == 0)
	   return 'x';
	else 
	   return 'o';   
}
int NewOrDuplicate(string player,scoreBoard S[],int Rp1,int Rp2,int RD){
	int d=0;
	fstream f1("info.txt");
	for(int i=0;i<counter;i++){
		if(S[i].name==player){
			S[i].win+=Rp1;
			S[i].lose+=Rp2;
			S[i].draw+=RD;
			d=1;
		}
	f1<<S[i].name<<'\t'<<S[i].win<<'\t'<<S[i].draw<<'\t'<<S[i].lose<<'\n';
	}
	f1.close();
	if(d==0)
    	return 0;
	return 1;
}
void tablePrint(){
	cout<<"\t\t\t\t\t\t| "<<table[0]<<" | "<<table[1]<<" | "<<table[2]<<" | "<<endl;
	cout<<"\t\t\t\t\t\t| "<<table[3]<<" | "<<table[4]<<" | "<<table[5]<<" | "<<endl;
	cout<<"\t\t\t\t\t\t| "<<table[6]<<" | "<<table[7]<<" | "<<table[8]<<" | "<<endl;
}
bool full(){
	for(int i=0;i<9;i++)
	{
		if(table[i] !='x' && table[i] != 'o'){
			return true;
		}
	}
	return false;
}
bool is_win(){
	if(table[0]==table[1] && table[1]==table[2])
	  return false;
	else if(table[3]==table[4] && table[4]==table[5])
	  return false;
	else if(table[6]==table[7] && table[7]==table[8])
	  return false;
	else if(table[0]==table[3] && table[3]==table[6])
	  return false;
	else if(table[1]==table[4] && table[4]==table[7])
	  return false;
	else if(table[2]==table[5] && table[5]==table[8])
	  return false;
	else if(table[0]==table[4] && table[4]==table[8])
	  return false;
	else if(table[2]==table[4] && table[4]==table[6])
	  return false;
	else{
		return true;
	}	  	  	  	  	  	  	  
}

void Restart(){
	table[0]='1',table[1]='2',table[2]='3',table[3]='4',table[4]='5',table[5]='6',table[6]='7',table[7]='8',table[8]='9';
}
int main(){
	while(true){
	    cout<<"\t\t\t\t Tik-Tak-Toe"<<endl;
		cout<<"1) Start game "<<endl;
		cout<<"2) Scoreboard "<<endl;
		cout<<"3) Exit "<<endl;
		int n=0;
		cout<<"enter a number: ";
		cin>>n;
		if(n==1){
			int Rp1=0,Rp2=0,RD=0;
			ifstream co("counter.txt");
			co>>counter;
			co.close();
			ifstream f1("info.txt",ios::in);
			for(int i=0;i<counter;i++){
				f1>>S[i].name>>S[i].win>>S[i].draw>>S[i].lose;
			}
			f1.close();
		    getName();
			Restart();
			tablePrint();
			int turn=0;
			while(is_win() && full()){
				int a;
				if(turn % 2 == 0){
				cout<<"'"<<player1<<"'"<<" "<<"its your turn Enter your choice : ";
				cin>>a;
				}
				else{
				cout<<"'"<<player2<<"'"<<" "<<"its your turn Enter your choice : ";
				cin>>a;
				}
				if(a<1 || a>9){
					cout<<"Please enter a number between 1 and 9 "<<endl;
					cout<<"Enter your choice : ";
					cin>>a;
				}
				if(table[a-1]=='x' || table[a-1]=='y'){
					cout<<"'"<<a<<"'"<<" already entered"<<endl;
					cout<<"choose another one:";
					cin>>a;
				}
				table[a-1]=X_or_O(turn);
				turn++;
				tablePrint();
			}
		    if(!is_win()){
		    	if(turn % 2==0){
		    		cout<<"congratulations '"<<player2<<"'";
		    		Rp2++;
				}
				else{
		    		cout<<"congratulations '"<<player1<<"'";
					Rp1++;					
				}
			cout<<" you won"<<endl;
			cout<<endl;
			}
			else if(!full()){
				cout<<"Draw try again"<<endl;
				RD=1;
			}
			fstream f12("info.txt",ios::app);
			if(NewOrDuplicate(player1,S,Rp1,Rp2,RD)==0){
				f12<<player1<<'\t'<<Rp1<<'\t'<<RD<<'\t'<<Rp2<<'\n';
				counter++;
			}
			if(NewOrDuplicate(player2,S,Rp2,Rp1,RD)==0){
				f12<<player2<<'\t'<<Rp2<<'\t'<<RD<<'\t'<<Rp1<<'\n';
				counter++;
			}
		}
		else if(n==2){
			string N;
			int w,l,d;
			ifstream f12("info.txt",ios::in);
			while(f12>>N>>w>>d>>l)
			 cout<<N<<'\t'<<w<<'\t'<<d<<'\t'<<l<<endl;
			 f12.close();
		} 
		else if(n==3){
			break;
		}
	}
}