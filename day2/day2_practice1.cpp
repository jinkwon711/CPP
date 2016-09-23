//============================================================================
// Name        : day2_practive1.cpp
// Author      : jin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {

	int arr[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};

	cout <<*arr << " "<< arr[0] << endl;
	cout <<*(arr+4) << " " << arr[4]<<endl;
	cout << *arr+4 << " " << arr[0]+4 << endl;

	int a = 8, b = 4;
	a = b = 0;
	cout << a << " " << b << endl;

	int c = 8, d = 4;
	(c = d) = 0;
	cout<< c << " "<< d << endl;

	int i = 0;
	cout<< i++<<endl;
	cout<< ++i<<endl;

	arr[++i]=20;
	cout << arr[2] << endl;
	cout << arr[3] << endl;

	arr[i++] = 30;
	cout << arr[3] << endl;
	cout << arr[4] << endl;

	int array[10];
	int *p1[10];
	int (*p2)[10] =&arr;





	return 0;
}
