//============================================================================
// Name        : day3_hw1.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

char canvas[50][50];
class Pixel{
private:

	int row =0;
	int col =0;
	int temp;
	char originalColor ='0';

public:
//	Pixel() = default;
//	Pixel(int M, int N): row(M), col(N){}


	void hi(int M, int N){
		row = M;
		col = N;
		for(int i=0; i!= M; i++){
			for(int j=0; j!=N; j++){
				canvas[i][j] ='O';
			}
		}
	}

	void clean(){
		for(int i=0; canvas[i][0]!=0; i++){
			for(int j=0; canvas[0][j]!=0; j++){
				canvas[i][j] = 'O';
			}
		}
	}
	void mark(int X, int Y, char C){;
		canvas[Y-1][X-1]= C;
	}
	void vertical(int X, int Y1, int Y2, char C){

//		cout<<"he"<<endl;
		for(int i = Y1-1; i!=Y2;i++){
			canvas[i][X-1]=C;
		}
	}
	void horizon(int X1, int X2, int Y, char C){

		for(int i = X1-1; i!=X2;i++){
			canvas[Y-1][i]=C;
		}
	}
	void fill(int X1, int Y1, int X2, int Y2, char C){
		for(int i=X1-1; i!=X2;i++){
			for(int j=Y1-1; j!=Y2; j++){
				canvas[j][i]=C;
			}
		}
	}
	void rect(int X1, int Y1, int X2, int Y2, char C){

		for(int i =X1-1; i!=X2;i++){
			canvas[Y1-1][i]=C;
		}
		for(int i =X1-1; i!=X2;i++){
			canvas[Y2-1][i]=C;
		}
		for(int i =Y1-1; i!=Y2;i++){
			canvas[i][X1-1]=C;
		}
		for(int i =Y1-1; i!=Y2;i++){
			canvas[i][X2-1]=C;
		}
	}
	void change(int X, int Y, char C){
		originalColor = canvas[Y-1][X-1];
		canvas[Y-1][X-1]=C;
		recursive(X,Y,C);
	}
	void recursive(int X, int Y, char C){
		//to top
		if(X-1>0 && Y-1>0  && canvas[Y-2][X-1]==originalColor){
			canvas[Y-2][X-1]= C;
			recursive(X, Y-1, C);
		}
		// to left
		if((X-1>0)&&( canvas[Y-1][X-2]==originalColor )){
			canvas[Y-1][X-2]= C;
			recursive(X-1, Y, C);
		}
		// to right
		if((Y<row+1)&&(canvas[Y-1][X]==originalColor )){
			canvas[Y-1][X]= C;
			recursive(X+1, Y, C);
		}
		// to bottom
		if((X<col+1)&&( canvas[Y][X-1]==originalColor )){
			canvas[Y][X-1]= C;
			recursive(X, Y+1, C);
		}

	}
	void bye(){
		for(int i =0; i!=row; i++){
			for(int j=0; j!=col; j++){
				cout<<canvas[i][j];
			}
			cout<<endl;
		}
	}



};


int main() {
	string line,command;
	vector<string> commandList;

	Pixel test;

	while(getline(cin,line)){
		istringstream ss(line);
		while(ss>>command){
			commandList.push_back(command);
//			cout<<commandList[0]<<commandList[1]<<endl;
		}

		if(commandList[0]=="hi"){
			int M = stoi(commandList[1]);
			int N = stoi(commandList[2]);
			test.hi(M,N);

		}
		else if(commandList[0]=="clean"){
			test.clean();
		}
		else if(commandList[0]=="mark"){
			int M = stoi(commandList[1]);
			int N = stoi(commandList[2]);
			char C = commandList[3][0];
			test.mark(M,N,C);

		}
		else if(commandList[0]=="vertical"){
			int X = stoi(commandList[1]);
			int Y1 = stoi(commandList[2]);
			int Y2 = stoi(commandList[3]);
			int C = commandList[4][0];
			test.vertical(X,Y1,Y2,C);
		}
		else if(commandList[0]=="horizon"){
			int X1 = stoi(commandList[1]);
			int X2 = stoi(commandList[2]);
			int Y = stoi(commandList[3]);
			int C = commandList[4][0];
			test.horizon(X1,X2,Y,C);
		}
		else if(commandList[0]=="fill"){
			int X1 = stoi(commandList[1]);
			int Y1 = stoi(commandList[2]);
			int X2 = stoi(commandList[3]);
			int Y2 = stoi(commandList[4]);
			int C = commandList[5][0];
			test.fill(X1,Y1,X2,Y2,C);
		}
		else if(commandList[0]=="rect"){
			int X1 = stoi(commandList[1]);
			int Y1 = stoi(commandList[2]);
			int X2 = stoi(commandList[3]);
			int Y2 = stoi(commandList[4]);
			int C = commandList[5][0];
			test.rect(X1,Y1,X2,Y2,C);
		}
		else if(commandList[0]=="change"){
			int X = stoi(commandList[1]);
			int Y = stoi(commandList[2]);
			char C = commandList[3][0];
			test.change(X,Y,C);
		}
		else if(commandList[0]=="bye"){
			test.bye();
			return 0;
		}
		commandList.clear();

	}



	return 0;
}
