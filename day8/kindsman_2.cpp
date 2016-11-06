#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>
#include <assert.h>
#include <sstream>
using namespace std;
//global variable

vector<string> temp1;
vector<string> temp2;
vector<string> combination;
int failure=0;
//동일 캐릭터가 있으면 true반환.
void go(int offset, int k) { // k is size of the word vector temp.
      if (k == 0) {
        string tempo="";
        sort(temp2.begin(),temp2.end());
        do {
          for(auto & it:temp2){
            tempo+=it+' ';
          }
          combination.push_back(tempo);
          cout<<tempo<<endl;
          tempo ="";
        } while ( next_permutation(temp2.begin(),temp2.end()));
        return;
      }

      for (int i = offset; i <= temp1.size() - k; ++i) {
        temp2.push_back(temp1[i]);
        go(i+1, k-1);
        temp2.pop_back();
    }
  }



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
void update_lookupTable(unordered_map<char,char> &m,unordered_map<char,char> &t,unordered_map<char,char> &t2){

  // for(auto &tm:t){
  //           cout<<"t값"<<tm.first<<"-"<<tm.second<<endl;
  //         }
  int exist =0;
  pair<char,char> temp;
  if(m.empty()){
    m=t;
    return;
  }
  for(auto &it:t){//temp
    for(auto &it2:m){//original
      if(it.first==it2.first){//if the alphabet is same;
        exist = 1;
              // cout<<it2.first<<endl;
              // cout<<"exist="<<exist<<endl;

        if(it.second!=it2.second) {
          failure = 1;
          return;
        }//failed to decode cryptogram;
        break;//because we already checked if there is duplicate in tempMap; once we find the right match, we don't have to search more.

        }
      }
    // cout<<"exist="<<exist<<endl;
    // cout<<temp.first<<":"<<temp.second<<endl;
    if(exist==0){
      t2.insert(it);//update a lookupTable with new pair;
    }
    exist=0;
  }

// for(auto &tm:t2){
//             cout<<"t2값"<<tm.first<<"-"<<tm.second<<endl;
//           }
  for(auto &it:t2){
    m.insert(it);

  }
      t2.clear();



}
int main(){
  int numOfWords;
  string sentence;
  string word;
  vector<string> dictionary;
  vector<string> secret;
  // vector<string> word_list;
  string answer="";

  vector<vector<string> > vec1;
  vector<string> vec2;

  
  int arr1[101];
  int arr2[101];


  unordered_map<char,char> lookupTable;
  unordered_map<char,char> tempMap;
  unordered_map<char,char> tempMap2;


  for(auto &it:arr1){
    it = 0;
  }//initailize
  cin>>numOfWords;
  // for dictionary creation
  for(int i=0; i!=numOfWords; i++){
    cin>>word;
    cin.ignore(256, '\n');

    dictionary.push_back(word);
  }

  getline(cin,sentence);
  istringstream ss(sentence);
  while(ss>>word){
    secret.push_back(word);
  }

  stable_sort(secret.begin(),secret.end(),[](const string &m,const string &n){return m.length()>n.length();});
  stable_sort(dictionary.begin(),dictionary.end(),[](const string &m,const string &n){return m.length()>n.length();});

  // for(auto &it:secret){
  //   cout<<it<<endl;
  // }// to find if sorting was done properly

  for(auto it:secret){
    arr1[it.length()]++;
  }//now arr1 contains numbers which matches the number of same length string in secret

  for(int i=1; i!=101;i++){
    if(arr1[i]!=0){
      for(auto &it1:dictionary){
        if(it1.length() == i){
          temp1.push_back(it1);//push words that has same lengths in the temp;
          // cout<<it1<<endl;
        } 
      }

      if(temp1.size()!=1){
        go(0,arr1[i]);// it stores from temp1 into temp2 and temp2 stores 
      }
      else{
        combination.push_back(temp1[0]);
      }
      temp2.clear();
      temp1.clear();
      vec1.push_back(combination);
      combination.clear();

    }
  }


  for(auto &it1:vec1){
    for(auto &it2:it1){
      cout<<it2<<endl;
    }
  }





//   for(auto &secretWord:secret){
//     for(auto&dictWord:dictionary){
//       if(secretWord.length()==dictWord.length()){
//         //from here to next quote - > check the duplicate match. if ,fail, if not, go on.
//         for(int i=0; i!=(signed)dictWord.length(); i++){
//           tempMap.insert({secretWord[i],dictWord[i]});
//         }//create tempMap to compare the size
//         if(tempMap.size()!=secretWord.length()){//if it is not same there exist duplicate
//           if(check_duplicate(secretWord,dictWord)){
//           //check if there is a word that have more than 2 values
//             cout<<"mission failure..."<<endl;
//             return 0;
//           }
//         }
//           // for(auto &tm:tempMap){
//           //   cout<<tm.first<<"-"<<tm.second<<endl;
//           // }
//         // temporary map compareed with original table;
//           //call map element duplication check
//           update_lookupTable(lookupTable,tempMap,tempMap2);
//           if(failure==1){
//             cout<<"mission failure..."<<endl;
//             return 0;
//           }
//           tempMap.clear();
//         }
//       }
//       //update the answer line before decoding process with space
//       // word_list.push_back(dictWord);
//       answer += secretWord+" ";
//     }

// //print all values in map;

//     // for(auto &it:lookupTable){
//     //   cout<<it.first<<":"<<it.second<<endl;
//     // }


// // both update and print the answer;
//     cout<<answer<<endl;

//   try{
//     for(int i=0; i!=answer.length()-1;i++){
//       if(answer[i]!=' '){//if it is not space
//         answer[i] = lookupTable.at(answer[i]);
//       }
//     }
//   }catch(out_of_range){
//     cout<<"mission failure..."<<endl;
//     return 0;
//   }

//     cout<<answer<<endl;



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
  // for(auto &it:dictionary){
  //   cout<<it<<endl;
  // }

  // for(auto &it:secret){
  //   cout<<it<<endl;
  // }


  return 0;
}
