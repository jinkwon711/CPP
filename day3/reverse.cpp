#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

int main(void){
    string input;
    string word;
    vector<string> wordList;
    cin>>input;

    reverse(input.begin(),input.end());
    cout<<input.size()<<endl;
    cout<<input.length()<<endl;
    cout<<input.back()<<endl;
    cout<<input<<endl;

   char a = '1';

   char &str = a;

   cout<<stoi(a)+1<<endl;




}
