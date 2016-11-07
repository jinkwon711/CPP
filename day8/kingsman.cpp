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
            tempo+=it;
          }
          combination.push_back(tempo);
          // cout<<tempo<<endl;
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

int main(){
  int numOfWords;
  string sentence;
  string word;
  vector<string> dictionary;
  vector<string> secret;
  string answer="";
  string original_secret_sentence="";

  vector<vector<string> > vec1;
  vector<string> vec2;
  
  int arr1[101];


  unordered_map<char,char> lookupTable;


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

  for(auto &it:secret){
    original_secret_sentence+=it+" ";
  }

  stable_sort(secret.begin(),secret.end(),[](const string &m,const string &n){return m.length()>n.length();});
  stable_sort(dictionary.begin(),dictionary.end(),[](const string &m,const string &n){return m.length()>n.length();});

  // for(auto &it:secret){
  //   cout<<it<<endl;
  // }// to find if sorting was done properly

  for(auto it:secret){
    arr1[it.length()]++;
  }//now arr1 contains numbers which matches the number of same length string in secret

  for(int i=100; i!=0;i--){
    if(arr1[i]!=0){
      for(auto &it1:dictionary){
        if(it1.length() == i){
          temp1.push_back(it1);//push words that has same lengths in the temp;
          // cout<<it1<<endl;
        } 
      }
      // cout<<"temp1 size : "<<temp1.size()<<endl;
      if(temp1.size()!=1){
        if(temp1.size()==0){
          cout<<"mission failure..."<<endl;
          return 0;
        }
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



  // for(auto &it1:vec1){
  //   for(auto &it2:it1){
  //     cout<<it2<<endl;
  //   }
  // }
  // cout<<endl;
  // cout<<endl;
  string dict_words;

int totalCombi=1;
  for(int i=0; i!=vec1.size();i++){
    totalCombi *=vec1[i].size(); 
  }


int k=0;
int mul = 1;
int first = 1;
for(int i=0; i!=vec1.size();i++){
  mul*=vec1[i].size();
  for(int j=0; j!=totalCombi; j++){

    if(j%(totalCombi/mul)==0) {
      k++;
      if(k==vec1[i].size()) k=0;
    }
    if(i==0){
      vec2.push_back(vec1[i][k]);
    }
    else{
      vec2[j] +=vec1[i][k];

    }
  }

  k=0;
}

// k=0;
// for(int i=0;i!=vec2.size();i++){
//   if(vec2.size()%vec1.size()==0) k=0;
  
//   vec2[k%totalCombi]+=vec2[k];
//   k++;
// }

// for(auto&it:vec2){
//   cout<<it<<endl;
// }
string secret_sentence="";
for(auto &it:secret){
  secret_sentence +=it;
}

// cout<<secret_sentence<<endl;

// cout<<secret_sentence.length()<<endl;
// cout<<vec2[0].length()<<endl;

char value;
pair<char,char> temp;
string finalAnswer="";
for(auto &pos_sentence: vec2){
  lookupTable.clear();
  lookupTable.insert({' ',' '});
  for(int i=0; i!=secret_sentence.length();i++){
    temp = {secret_sentence[i],pos_sentence[i]};
    try{
      value = lookupTable.at(secret_sentence[i]);
    }catch(out_of_range){
      lookupTable.insert(temp);
    }
    if(value==pos_sentence[i]){
      failure = 0;
    }
    else{
      failure = 1;
    }
  }
 
  if(failure==0){
    for(int i=0; i!=original_secret_sentence.length(); i++ ){
       finalAnswer+=lookupTable.at(original_secret_sentence[i]);
    }
    for(int i=0; i!=original_secret_sentence.length()-1;i++){
      cout<<finalAnswer[i];
    }
    cout<<endl;
    return 0;
  }
}

   cout<<"mission failure..."<<endl;

  return 0;
}
