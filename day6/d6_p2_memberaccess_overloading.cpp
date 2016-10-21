#include <iostream>

using namespace std;

struct tresure{
  int secret;
};

struct key {
  tresure *t;

  tresure *operator->() const{

    return t;
  }

  bool operator()() const{
      if(t ==nullptr) return false;
      else return true;
  }
};

int main(){
  tresure t = {42};
  key k1 = {&t};
  key k2 = {nullptr};

  auto validate = [](key k)->bool{
    if(k.t==nullptr)return false;
    else return true;

  };

  if(validate(k1))cout<<k1->secret <<endl;
  else cout<<"Can't reveal the secret with k1"<<endl;

  if(validate(k2))cout<<k2->secret <<endl;
  else cout<<"Can't reveal the secret with k2"<<endl;

  if(k1()) cout<<k1->secret<<endl;
  else cout<<"Can't reveal the secret with k1"<<endl;

  if(k2()) cout<<k2->secret<<endl;
  else cout<<"Can't reveal the secret with k2"<<endl;

  return 0;

}
