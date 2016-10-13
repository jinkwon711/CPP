//============================================================================
// Name        : day5_hw1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
using namespace std;



int main() {
	int number;
	scanf("%d",&number);
	int temp;
	int count[10001];

	for(auto &it:count){
		it = 0;
	}

	for(int i =0; i!=number; i++){
		scanf("%d",&temp);
		count[temp]++;
	}


	for(int i=1;i<=10000;i++){
		while(count[i]!=0){
			printf("%d\n",i);
			count[i]--;
		}
	}

	return 0;
}
