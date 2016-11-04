#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>
#include <assert.h>
using namespace std;
//global variable
int failure=0;
//동일 캐릭터가 있으면 true반환.

bool check_duplicate(string w1,string w2){
  for(int i=0; i!=w1.length(); i++){
    for(int j=0; j!=w1.length();j++){
      if(i!=j){
        if(w1[i]==w1[j]){
          if(w2[i]!=w2[j]) return true;
        }
      }
    }
  }
  return false;
}
void update_lookupTable(unordered_map<char,char> &m,unordered_map<char,char> &t){
  int exist =0;
  pair<char,char> temp;
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
      temp=it2;
    }
    if(exist==0){
      m.insert(temp);//update a lookupTable with new pair;
    }
    exist=0;
  }


}
int main(){
  int numOfWords;
  string word;
  vector<string> dictionary;
  vector<string> secret;
  unordered_map<char,char> lookupTable;
  unordered_map<char,char> tempMap;

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
        for(int i=0; i!=(signed)dictWord.length(); i++){
          tempMap.insert({secretWord[i],dictWord[i]});
          if(tempMap.size()!=secretWord.length()){

            if(check_duplicate(secretWord,dictWord)){ //check if there is a word that have more than 2 values
              cout<<"mission failure..."<<endl;
              return 0;
            }


          }
          //if there is duplicate char in the secret word with same mapping value->failure
                    //creatring temporary map to compare with original table;
        }
        for(int i=0; i!=(signed)dictWord.length();i++){
          //call map element duplication check
            update_lookupTable(lookupTable,tempMap);
          }
        }


        //call map append function

      }
    }
  //
// char tempo,tempo2;
// for(int i=0; i!=3;i++){
//   cin>>tempo>>tempo2;
//   lookupTable.insert({tempo,tempo2});
// }
//
// cout<<lookupTable.size()<<endl;
// cout<<lookupTable.at('a')+1<<endl;


//print sample test
  for(auto &it:dictionary){
    cout<<it<<endl;
  }

  for(auto &it:secret){
    cout<<it<<endl;
  }


  return 0;
}
