//============================================================================
// Name        : day2_practice2.cpp
// Author      : jin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	int number, width;
	cin >> number;
	width = number*2 -1;

	for(int i =1; i !=number; i++){
			for( int j =1 ; j != width+1; j++){
				if(i==1 && j == ((width+1)/2-(i-1))){
					cout<<"*"<<endl;
					break;
				}
				else if(j == ((width+1)/2-(i-1))){
					cout<<"*";
				}
				else if(j==((width+1)/2+(i-1))){
					cout<<"*"<<endl;
					break;
				}
				else{
					cout<<" ";
				}
			}
	}
	for(int i = 0; i!=width;i++){
			cout<<"*";
		}

	return 0;
}
