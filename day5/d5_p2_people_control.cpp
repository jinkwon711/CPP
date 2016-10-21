#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
  multimap<string,string> list;
  string input;
  string command1;
  string command2;
  string command3;
  vector<string> names;
  bool exist = false;



  while(getline(cin,input)){
    if(input=="end"){
      return 0;
    }
    stringstream ss;
    ss.str(input);
    ss>>command1;
    ss>>command2;
    ss>>command3;

    if(command1=="add"){
    list.insert({command3,command2});
    }
    else if(command1=="exist"){
      for(auto it = list.begin(); it!=list.end(); it++){
        if(it->second == command2){
          exist = true;
        }
      }
      if(!exist){
        cout<<"no"<<endl;
      }else{
        cout<<"yes"<<endl;
        exist=false;
      }
    }
    else if(command1 =="print"){
      auto count = list.count(command2);
      auto k = list.find(command2);
      while(count){
        names.push_back(k->second);
        ++k;
        --count;
      }
      sort(names.begin(),names.end());
      for(auto &it:names){
        cout<<it<<endl;
      }
      names.clear();

    }
  }


  return 0;
}
