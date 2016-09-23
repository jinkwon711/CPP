//============================================================================
// Name        : day2_practice3.cpp
// Author      : jin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

	int max(int x, int y){
		if (x>y){
			return x;
		}
		else{
			return y;
		}
	}
	int max(int x, int y, int z){
		if(x>y){
			if(z>x){
				return z;
			}
			else{
				return x;
			}
		}else
			if(y>z){
				return y;
			}
			else{
				return z;
			}
	}
	int max(int *arr, int size){
		int answer = arr[0];
		for(int i=0; i!=size; i++){
			if(arr[i] > answer){
				answer =arr[i];
			}
		}
		return answer;
	}


int main() {
	int a = 0;
	int b = 2;
	int c = 3;
	int arr[8]= {2, 0, 1, 6, 0, 9, 2, 3};

	cout<< max(a, b)<<endl;
	cout<< max(a, b, c )<< endl;
	cout<< max(arr, 8)<< endl;

	return 0;
}
