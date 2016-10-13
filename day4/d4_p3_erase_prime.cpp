//============================================================================
// Name        : day4_practice3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int cnt=0;
	int number;
	double temp;
	string input;
	vector<int> numList;
	vector<int> uniqueList;
	vector<int>	primeList;



	while(cin>>number && number != -1){
		for(int i=2; i<=number/2;++i){
			if(number%i==0){
				cnt=1;
				break;
			}
		}
		if(cnt!=0){
			numList.push_back(number);
			cnt=0;
		}
	}
	sort( numList.begin(), numList.end() );
	numList.erase( unique( numList.begin(), numList.end() ), numList.end() );




	for(auto it:numList){
		cout<<it<<" ";
	}

	return 0;

}
