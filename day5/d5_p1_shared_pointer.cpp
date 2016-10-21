#include <iostream>
#include <memory>
using namespace std;

void f(shared_ptr<int> k){
  return;
}

int main(){
  //shared count
  shared_ptr<int> p0(new int(1));
  cout<<p0.use_count()<<endl;  // ptr to int 1 count 1

  shared_ptr<int> p1(p0);
  cout<<p0.use_count()<<endl;// ptr to int 1 count 2

  weak_ptr<int> p2(p0);
  cout<<p0.use_count()<<endl;// ptr to int 1 count 2

  p0.reset(new int(3));ㄴ
  cout<<p0.use_count()<<endl;// ptr to int 3 count 1

  //be careful!
  int* p3 = p0.get(); //ptr to int 3 == p3,
  f((shared_ptr<int>)p3); //memory p0 points to is freed
  //함수로 넘겨줄 때 단순히 포인터 넘겨주면 안에서 카운트를 못하니 쉐어드 카운터로 넘겨주고
  //이 함수를 나올때 쉐어드 포인터의 카운트는 0이된다.ㄴ

  //unique_ptr
  unique_ptr<int> p4(new int(3));
  unique_ptr<int> p5(new int(4));
  cout<<*p4<<" "<<*p5<<endl;// p4 point to 3, p4 point to 4;

  //unique_ptr<int> p6(p4);
  unique_ptr<int> p6(p4.release()); //p6 now point to p4's relased location, which is int 3;
  cout<<*p6<<endl; // p6 points to 3;

  return 0;
}
