#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <array>
using namespace std;

void simple_function(){
  cout<<"Simple Functor"<<endl;
}

int main(void){
  int a=10, b=1000;
  void (*pf)() = simple_function;

  [](){cout<<"Simple Lambda function"<<endl;}();

  auto lambda_p= [](int a,int b) { cout << "A is "<< a <<endl; cout<<"B is " <<b<<endl;};

  [=](){cout<<"Capture by value!"<<" " << a << " " << b<<endl;}();

  [&](){cout<<"Capture by reference!"<<" " << a << " " << b<<endl;}();

  [=] () mutable{a+=1; b+=1; cout<< "Mutable!"<<" " << a << " " << b<<endl;}();


  auto sum_lambda = [=]() ->int{return a+b;}();
  cout<< sum_lambda<<endl;

  auto sum_lambda2= [=] () {return a+b;}();
  cout<<sum_lambda2<<endl;


  return 0;


}
