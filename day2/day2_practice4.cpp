//============================================================================
// Name        : day2_practice4.cpp
// Author      : jin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
void move(int n,int start, int goal){
	cout<<n<<" : "<<start<<" -> "<<goal<<endl;
}

int tower(int n , int start,int temp, int goal){
	if (n==0){
		return 0;
	}
	tower(n-1, start, goal , temp);
	move(n,start, goal);
	tower(n-1, temp ,start, goal);

	return 0;
}

int main() {
	int n, start, goal, temp;
	cin>>n>>start>>goal;
	temp = 6-start-goal;

	tower(n,start,temp,goal);

	return 0;
}
