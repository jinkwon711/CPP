#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

class BigInteger{
private:
    char arr[101];
    char result[350];
    string value;


public:
    //constructor
    BigInteger(string a): value(a){}

    // operator overloading

    // BigInteger &operator=(const BigInteger &bi){
    //     value = bi.value;
    //     return *this;
    // }

    BigInteger operator+(const BigInteger& bi1, const BigInteger& bi2){
        addition(bi1,bi2);
    }



    addition (BigInteger bi1, BigInteger bi2){
        int c1 = 100-bi1.value.length();
        int c2 = 100-bi2.value.length();
        int x, y;

        for (int i =99; i>= c1; i--){
            y=
        }


        int cycle;
        string &str1 = bi1.value;
        string &str2 = bi2.value;
        reverse(str1.begin(),str1.end());
        reverse(str2.begin(),str2.end());
        if(str1.size()>=str2.size()){
            cycle = str2.size();
            for(int i = cycle; i!=str1.size();i++){
                str1+'0';
            }
        }
        }else
        {
            cycle = str1.size();
            for(int i = cycle; i!=str1.size();i++){
                str1+'0';
            }
        }
        int overTen=0;
        int cnt=0;
        for(int i=0; i!=cycle; i++){
            result[i] = (to_string((str1[i])-'0')+(str2[i]-'0')+overTen).[1]
            if(((str1[i])-'0')+(str2[i]-'0')+overTen>=10){
                overTen=1;
            }
            else{
                overTen=0;
            }
        }
    return bi1;


        }
    }
};

int main(void){
    string line,oper;
    vector<string> calList;
    string newline;
    bool cnt;

    getline(cin,line);

    cout<<line<<endl;
    for(auto &it:line){
        if(it=='*' || it=='+'){
            newline += ' ';
            newline += it;

            cnt = true;
        }
        else if(isdigit(it)){
            if(cnt==true){
                cnt=false;
                newline += ' ';
            }
            newline += it;
        }

    }

    istringstream ss(newline);
    while(ss>>oper){ calList.push_back(oper);}

    for(int i= 0; i!=calList.size();i++){
        cout<<calList[i]<<"  "<<endl;
    }
};