//============================================================================
// Name        : day1_hw2.cpp
// Author      : jinhwan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {

	int number1 = 88, number2 = 22;

	int *pNumber1 = &number1;
	*pNumber1 = 99;

	cout << *pNumber1 <<endl;
	cout << &number1 <<endl;
	cout << pNumber1 <<endl;
	cout << &pNumber1 <<endl;
	pNumber1 = &number2;

	int &refNumber1 = number1;
	refNumber1 = 11;
	cout << refNumber1 << endl;
	cout << &number1 << endl;
	cout << &refNumber1 << endl;
	//refNumber1 = &number2;
	refNumber1 = number2;

	number2++;
	cout << refNumber1 << endl;
	cout << number1 << endl;
	cout << number2 << endl;

	return 0;

}

