#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <cctype>
#include <algorithm>
#include <string>
using namespace std;

char selection='o';
char comp='x';
string pre_selection;
void rules();
char player_choice();
char computer_choice();
int user_turn(char[9]);
void player_display(char[9]);
int computer_turn(char[9],string);
int minimax(char[9],int,bool,int&);
void computer_display(char[9]);
int check_winner(char[9]);
void match_result(int value);
void display(char[9]);
int easy(char[9]);
int medium(char[9]);
int random(char[9]);
int easy_move(char[9]);

int main(){
	rules();
	selection=player_choice();
	comp=computer_choice();
	string level{};
	cout<<"\nSelect difficulty level(Easy/Medium/Hard): ";
		do{
			cin>>level;
			transform(level.begin(),level.end(),level.begin(),::tolower);
			if(level!="easy" && level!="medium" && level!="hard")
				cout<<"Invalid input-try again\n";
		}while(level!="easy" && level!="medium" && level!="hard");
	system("cls");
	cout<<"Here we go!!!!"<<endl<<endl;
	int move{};
	int k{};
char moves[9]{' ',' ',' ',' ',' ',' ',' ',' ',' '};
	int value{2};
	while(k<9 && value>1){
		move=user_turn(moves);
		system("cls");
		moves[move-1]=selection;
		player_display(moves);
		++k;
		if(k>=4){
			value=check_winner(moves);
		}
		if(k<9 && value>1){
			this_thread::sleep_for(0.6s);
			system("cls");
			move=computer_turn(moves,level);
			moves[move]=comp;
			computer_display(moves);
			++k;
			if(k>=4){
				value=check_winner(moves);
			}
		}
	}
	this_thread::sleep_for(0.2s);	
	match_result(value);
	cout << endl;
	cout<<"\nWant to play again?(Yes/No) ";
	string ch{};
	cin>>ch;
	transform(ch.begin(),ch.end(),ch.begin(),::tolower);
	if(ch=="yes"){
		system("cls");
		main();
	}
	else{
		cout<<"Good Bye"<<endl;
		return 0;
	}
//	return 0;
}
void rules(){
	char arr[]{'1','2','3','4','5','6','7','8','9'};
	cout<<"Hey user! Let's play Tic-Tac-Toe"<<endl;
	cout<<"Rules :-"<<endl
		<<"The grid is numbered as follows:"<<endl;
	display(arr);
	cout<<"First tou are required to select the letter with which you want to play - X or O"<<endl
		<<"You are supposed to enter a number which will be the position where you want to insert the letter"<<endl
		<<"The player who gets 3 consecutive Xs or Os(horizontally, vertically or diagonally) wins"<<endl;
}
char player_choice(){
	char choice;
	do{
		cout<<endl<<"Choose your letter: ";
		cin>> pre_selection;
		if(pre_selection.length()>1)
			cout<<"Please choose either \"X\" or \"O\""<<endl;
		else{
			choice=pre_selection[0];
			choice=toupper(choice);
			if(choice!='X' && choice!='O'){
				if(choice!='X' && choice!='O'){
					cout<<"Please choose either \"X\" or \"O\""<<endl;
				}
			}
		}
	}while(choice!='X' && choice!='O');
	return choice;
}
char computer_choice(){
	char computer;
	if(selection=='X'){
		computer='O';
	}
	else
		computer='X';
	return computer;
}
int user_turn(char turns[9]){
	int turn{};
	cout<<endl<<"Your turn..."<<endl;
		do{
			cout<<"Make your move: ";
//			cin>>turn;
			while(!(cin>>turn)){
				cout<<"ERROR- Enter an integer from 1 to 9: ";
				cin.clear();
				cin.ignore(22,'\n');
			}
			if(turns[turn-1]!=' '){
				cout<<"Invalid move-try again"<<endl;
			}
		}while(turns[turn-1]!=' ');
		return turn;
}
void player_display(char turns[9]){
	display(turns);
//	cout<<"================================"<<endl<<endl;
}
int computer_turn(char turns[9], string difficulty){
	if(difficulty=="easy"){
		return easy(turns);
	}
	else if(difficulty=="medium"){
		return medium(turns);
	}
	else{
		int bestval=1000;
		int move{-1};
		int t1{1000};
		int t2{-1000};
		for(int i{};i<9;++i){
			int lessval{};
			int count{};
			if(turns[i]==' '){
				turns[i]=comp;
				lessval=minimax(turns,0,false,count);
				turns[i]=' ';
				if(lessval<=bestval){
					if(lessval==-1 && count<t1){
						move=i;
						bestval=lessval;
						t1=count;
					}
					else if(lessval==1 && count>t2){
						move=i;
						bestval=lessval;
						t2=count;
					}
					else{
						move=i;
						bestval=lessval;
					}
				}
			}
		}
		return move;
	}
	
}
int minimax(char turns[9],int depth,bool isMin,int& c){
	int score=check_winner(turns);
	if(score==1){
		return 1;
	}
	if(score==-1){
		return -1;
	}
	if(score==0){
		return 0;
	}
	if(isMin){
		int best=1000;
		for(int i{};i<9;++i){
			if(turns[i]==' '){
				turns[i]=comp;
				best=min(best,minimax(turns,depth+1,!isMin,c));
				turns[i]=' ';
			}
		}
		++c;
		return best;
	}
	else{
		int best=-1000;
		for(int i{};i<9;++i){
			if(turns[i]==' '){
				turns[i]=selection;
				best=max(best,minimax(turns,depth+1,!isMin,c));
				turns[i]=' ';
			}
		}
		++c;
		return best;
	}
}
void computer_display(char turns[9]){
	display(turns);
}
int check_winner(char turns[9]){
	if((turns[0]==selection && turns[4]==selection && turns[8]==selection) || (turns[2]==selection && turns[4]==selection && turns[6]==selection)){
		return 1;
	}
	if((turns[0]==comp && turns[4]==comp && turns[8]==comp) || (turns[2]==comp && turns[4]==comp && turns[6]==comp)){
		return -1;
	}
	for(int j{};j<9;j+=3){
		if(turns[j]==selection && turns[j+1]==selection && turns[j+2]==selection){
			return 1;
		}
		if(turns[j]==comp && turns[j+1]==comp && turns[j+2]==comp){
			return -1;
		}
	}
	for(int j{};j<3;++j){
		if(turns[j]==selection && turns[j+3]==selection && turns[j+6]==selection){
			return 1;
		}
		if(turns[j]==comp && turns[j+3]==comp && turns[j+6]==comp){
			return -1;
		}
	}
	for(int i{};i<9;++i){
		int count{};
		if(turns[i]==' '){
			++count;
		}
		if(count>0){
			return count+5;
		}
	}
	return 0;
}
void match_result(int value){
	if(value==1){
		cout<<"YOU WIN";
	}
	else if(value==-1){
		cout<<"YOU LOSE";
	}
	else{
		cout<<"TIE";
	}
}
void display(char sequence[9]){
	for(int i{1};i<=9;++i){
		if(i%3==0 && i!=9){
			cout<<"_________|_________|_________"<<endl;
		}
		else if(i%3!=0 && (i+1)%3!=0){
			cout<<"	 |	   |	"<<endl;
		}
		else if(i%3!=0 && (i+1)%3==0){
			cout<<"    "<<sequence[i-2]<<"    |    "<<sequence[i-1]<<"    |    "<<sequence[i]<<"    "<<endl;
		}
		if(i==9){
			cout<<"	 |	   |	 ";
		}
	}cout<<endl;
}
int random(char turn[9]){
	int move{};
	do{
		srand(time(0));
		move=rand()%9;
	}while(turn[move]!=' ');
	return move;
}
int easy_move(char turn[9]){
	int pcount{};
	int ccount{};
	for(int i{};i<9;i+=3){
		for(int j{};j<3;++j){
			if(turn[i+j]==comp){
				++ccount;
			}
		}
		if(ccount==2){
			for(int j{};j<3;++j){
				if(turn[i+j]==' '){
					return i+j;
				}
			}
		}
		ccount=0;
	}
	for(int i{};i<3;++i){
		for(int j{};j<3;++j){
			if(turn[i+(3*j)]==comp){
				++ccount;
			}
		}
		if(ccount==2){
			for(int j{};j<3;++j){
				if(turn[i+(3*j)]==' '){
					return i+(3*j);
				}
			}
		}
		ccount=0;
	}
	for(int i{2};i<=6;i+=2){
		if(turn[i]==comp){
			++ccount;
		}
	}
	if(ccount==2){
		for(int i{2};i<=6;i+=2){
			if(turn[i]==' '){
				return i;
			}
		}
	}
	ccount=0;
	for(int i{};i<=9;i+=4){
		if(turn[i]==comp){
			++ccount;
		}
	}
	if(ccount==2){
		for(int i{};i<=9;i+=4){
			if(turn[i]==' '){
				return i;
			}
		}
	}
	ccount=0;
	for(int i{};i<9;i+=3){
		for(int j{};j<3;++j){
			if(turn[i+j]==selection){
				++pcount;
			}
		}
		if(pcount==2){
			for(int j{};j<3;++j){
				if(turn[i+j]==' '){
					return i+j;
				}
			}
		}
		pcount=0;
	}
	for(int i{};i<3;++i){
		for(int j{};j<3;++j){
			if(turn[i+(3*j)]==selection){
				++pcount;
			}
		}
		if(pcount==2){
			for(int j{};j<3;++j){
				if(turn[i+(3*j)]==' '){
					return i+(3*j);
				}
			}
		}
		pcount=0;
	}
	for(int i{2};i<=6;i+=2){
		if(turn[i]==selection){
			++pcount;
		}
	}
	if(pcount==2){
		for(int i{2};i<=6;i+=2){
			if(turn[i]==' '){
				return i;
			}
		}
	}
	pcount=0;
	for(int i{};i<=9;i+=4){
		if(turn[i]==selection){
			++pcount;
		}
	}
	if(pcount==2){
		for(int i{};i<=9;i+=4){
			if(turn[i]==' '){
				return i;
			}
		}
	}
	pcount=0;
	return -1;
}
int easy(char turn[9]){
	int move=easy_move(turn);
	if(move==-1)
		return random(turn);
	return move;
}
int medium(char turn[9]){
	int move=easy_move(turn);
	if(move==-1){
		int ccount{};
		int ncount{};
		for(int i{};i<9;i+=3){
			for(int j{};j<3;++j){
				if(turn[i+j]==comp){
					++ccount;
				}
				if(turn[i+j]==' '){
					++ncount;
				}
			}
			if(ccount==1 && ncount==2){
				for(int j{};j<3;++j){
					if(turn[i+j]==' '){
						return i+j;
					}
				}
			}
			ccount=0;
			ncount=0;
		}
		for(int i{};i<3;++i){
			for(int j{};j<3;++j){
				if(turn[i+(3*j)]==comp){
					++ccount;
				}
				if(turn[i+(3*j)]==' '){
					++ncount;
				}
			}
			if(ccount==1 && ncount==2){
				for(int j{};j<3;++j){
					if(turn[i+(3*j)]==' '){
						return i+(3*j);
					}
				}
			}
			ccount=0;
			ncount=0;
		}
		for(int i{2};i<=6;i+=2){
			if(turn[i]==comp){
				++ccount;
			}
			if(turn[i]==' '){
				++ncount;
			}
		}
		if(ccount==1 && ncount==2){
			for(int i{2};i<=6;i+=2){
				if(turn[i]==' '){
					return i;
				}
			}
		}
		ccount=0;
		ncount=0;	
		for(int i{};i<=9;i+=4){
			if(turn[i]==comp){
				++ccount;
			}
			if(turn[i]==' '){
				++ncount;
			}
		}
		if(ccount==1 && ncount==2){
			for(int i{};i<=9;i+=4){
				if(turn[i]==' '){
					return i;
				}
			}
		}
		ccount=0;
		ncount=0;
		return random(turn);
	}
	else{
		return move;
	}
}