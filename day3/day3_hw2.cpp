#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int ord(int op){  // ascii  40 (, 41 ) ,42 * , 43 +, 45 - , 47 /
    if(op==40)return 0;
    if(op==42 || op==47) return 2;
    if(op==43 || op==45) return 1;

    return 3;
}

class BigInteger{

private:
    string number;

public:
    //constructor
    BigInteger()=default;

    BigInteger(string s):number(s){}
    //member function
    void setNum(string s){
        number = s;
    }
    string &getNum(){
        return number;
    }

    BigInteger operator + (BigInteger bi) {
        BigInteger result;
        result.setNum( addition(getNum(), bi.getNum() ) );
        return result;
    }

    // BigInteger operator * (BigInteger bi) {
    //     BigInteger result;
    //     result.setNum( multiply(getNum(), bi.getNum() ) );
    //     return result;
    // }

    string addition(string num1, string num2){
        int overTen = 0;
        int lengthDiff = abs((int)(num1.length()-num2.length()));
        string addition = (num1.length()> num2.length())? num1:num2;
        //override with the longer string;
        if(num1.length()>num2.length()){
            num2.insert(0, lengthDiff, '0');
        }
        else{
            num1.insert(0, lengthDiff, '0');
        }//num1, num2 lengths are equal

        for(int i=num1.length()-1; i>=0; i--){
            int temp = (overTen)+(num1[i]-'0')+(num2[i]-'0');
            if(temp>10){
                overTen=1;
                temp -=10;
            }
            else{
                overTen=0;
            }
            addition[i] = temp+'0';//result +'0' to char.
        }
        return addition;
    }

    string multiplication(string num1, string num2){

    }






};


int main(void){
    string line,oper;
    vector<BigInteger> calList;
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

    // istringstream ss(newline);
    // while(ss>>oper){calList.push_back(oper);}

    // for(int i= 0; i!=calList.size();i++){
    //     cout<<calList[i]<<"  "<<endl;
    // }
    string temp="";
    string val ="";
    vector<char> postfix;
    vector<BigInteger> cal;
    string process ="";
    for(auto &it: newline){
        if(isdigit(it)){
            val += it;
        }
        else{
            temp += (val)+ " ";
            // temp+=" ";
            val="";
            switch(it){
                case '(' :
                    postfix.push_back(it);
                    break;
                case ')' :
                    while(postfix.back() != '('){
                        temp += postfix.back();
                        postfix.pop_back();
                    }
                    postfix.pop_back(); //discard '('
                    break;
                case '+':
                case '-':
                case '*':
                case '/' :
                    if(!postfix.empty() && postfix.back()!='('){
                        while(ord(postfix.back())>=ord(it)){
                            if(postfix.empty()){
                                break;
                            }
                            temp+=postfix.back();

                            postfix.pop_back();
                        }
                    }
                    postfix.push_back(it);
                    break;
            }
        }
    }
    temp+= val+" ";


    for(unsigned int i =0; i!=postfix.size() ; i++){
        temp += postfix.back();
        postfix.pop_back();
        i--;
    }



    for(auto &it: temp){
        if(isdigit(it)){
            process += it;
        }
        else if(isspace(it)){
            if(!process.empty()){

                cal.push_back(BigInteger(process));
                process ="";
                }
            }
        else{
            BigInteger number2= cal.back();
            // cout<<"number2 :"<< number2<<endl;
            cal.pop_back();
            BigInteger number1 = cal.back();
            // cout<<number1<<endl;
            cal.pop_back();


            // cout<<"number1 :"<< number1<<endl;

            switch(it){
                case '+':
                cal.push_back(number1+number2);
                cout<<(number1+number2).getNum()<<endl;
                    break;
                // case '-':
                //     answer = (number1)-(number2);
                //     break;
                // case '*':
                //     answer = (number1)*(number2);
                //     break;
                // case '/':
                //     answer = (number1)/(number2);
                //     break;
            }
            // cout<<"answer :"<< answer<<endl;
            // cout<<cal[0]<<endl;
        }

    }
    cout<<cal[0].getNum()<<endl;



}