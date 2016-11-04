#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class User{
public:
  vector<string> received;
  vector<string> sent;
  vector<string> totalText;
  string name;

User(string n):name(n){}


};



int main(){
  int numOfUser, numOfText;
  vector<User> user_list;
  string tempName;
  string command;
  string user1;
  string user2;
  string text;
  cin>>numOfUser;

  for(int i=0; i!=numOfUser;i++){
    cin>>tempName;
    user_list.push_back(User(tempName));
  }
  cin>>numOfText;

  for(int i=0; i!=numOfText;i++){
    cin>>command;

    if(command=="send"){
      cin>>user1>>user2>>text;


      auto it1 = find_if(user_list.begin(),user_list.end(),[user1](const User& u){return u.name==user1;});
      auto it2 = find_if(user_list.begin(),user_list.end(),[user2](const User& u){return u.name==user2;});

      it1->sent.push_back("to <"+it2->name+">: "+text);
      it1->totalText.push_back("to <"+it2->name+">: "+text);
      it2->received.push_back("from <"+it1->name+">: "+text);
      it2->totalText.push_back("from <"+it1->name+">: "+text);
    }
    else if(command=="forward"){
      int messageNo;
      cin>>user1>>user2>>messageNo;
      auto it1 = find_if(user_list.begin(),user_list.end(),[user1](const User& u){return u.name==user1;});
      auto it2 = find_if(user_list.begin(),user_list.end(),[user2](const User& u){return u.name==user2;});
      string text= it1->received[messageNo-1];
      it1->sent.push_back("to <"+it2->name+">: "+text);
      it1->totalText.push_back("to <"+it2->name+">: "+text);
      it2->received.push_back("from <"+it1->name+">: "+text);
      it2->totalText.push_back("from <"+it1->name+">: "+text);
    }
}


for(auto &it:user_list){
  cout<<"@"<<it.name<<endl;
  for(auto &it2:it.totalText){
    cout<<it2<<endl;
  }
}







  return 0;
}
