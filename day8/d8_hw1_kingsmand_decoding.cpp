#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
using namespace std;
//global variable
int failure=0;
//동일 캐릭터가 있으면 true반환.
void update_lookupTable(map<char,char> &m,map<char,char> &t){
  int exist =0;
  if(m.empty()){
    m=t;
    return;
  }
  for(auto &it:m){
    for(auto &it2:t){
      if(it.first==it2.first){//if the alphabet is same;
        exist = 1;
        if(it.second!=it2.second) failure = 1;//failed to decode cryptogram;
      }
      if(exist==0){
        m.insert(it2);//update a lookupTable with new pair;
      }
      exist=0;
    }
  }


}
int main(){
  int numOfWords;
  string word;
  vector<string> dictionary;
  vector<string> secret;
  map<char,char> lookupTable;
  map<char,char> tempMap;

  cin>>numOfWords;
  //for dictionary creation
  for(int i=0; i!=numOfWords; i++){
    cin>>word;
    dictionary.push_back(word);
  }
  while(cin>>word){
    secret.push_back(word);
  }



  for(auto &secretWord:secret){
    for(auto&dictWord:dictionary){
      if(secretWord.length()==dictWord.length()){
        for(int i=0; i!=dictWord.length(); i++){
          tempMap.insert({secretWord[i],dictWord[i]});//creatring temporary map to compare with original table;
        }
        for(int i=0; i!=dictWord.length();i++){
          //call map element duplication check
            update_lookupTable(lookupTable,tempMap);
          }
        }


        //call map append function

      }
    }






//print sample test
  for(auto &it:dictionary){
    cout<<it<<endl;
  }

  for(auto &it:secret){
    cout<<it<<endl;
  }


  return 0;
}
