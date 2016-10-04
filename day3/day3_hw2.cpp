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

    BigInteger(string s):number(s){}

    string getNum(){
        return number;
    }

    BigInteger operator + (BigInteger bi) {
        BigInteger result(addition(getNum(), bi.getNum()));
        return result;
    }

    BigInteger operator * (BigInteger bi) {
        BigInteger result(multiplication(getNum(), bi.getNum() ) );
        return result;
    }

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
            if(temp>=10){
                overTen=1;
                temp -=10;
            }
            else{
                overTen=0;
            }
            addition[i] = temp+'0';//result +'0' to char.
        }
        if(overTen ==1){ // 마지막으로 넘어간값이 저장되지 않았을떄.
                addition.insert(0,1,'1');
        }
        return addition;
    }

    string multiplication(string num1, string num2){
        // cout<<"inside multiply"<<endl;
        string multiplication;
        if(num1.length()> num2.length()){
            num1.swap(num2);
        }
        //num2를 곱해지는 대상, num1을 하나씩 쪼개서 다 곱한다.
        for(int i=num1.length()-1; i>=0; i--){
            string result = num2;
            int overTen = 0;
            // cout<<"inside first for"<<endl;
            for(int j =result.length()-1;j>=0;j--){
                            // cout<<"inside second for"<<endl;
                int temp = ((result[j]-'0') * (num1[i]-'0'))+overTen;
                if (temp >=10){
                    overTen = (temp/10);
                    temp = temp - overTen*10;
                    // cout<<overTen<<endl;
                }
                else{
                    overTen = 0;
                }
                result[j] = temp+'0';
            }
            if(overTen>0){
                result.insert(0,1,(overTen+'0'));
            }
            result.append((num1.length()-i-1), '0');
            multiplication = addition(multiplication, result );
        }
        while(multiplication[0] =='0' && multiplication.length()!=1){
            multiplication.erase(0,1);
            // cout<<"hello"<<endl;
        }
        return multiplication;
    }
};

int main(void){
    string line,oper;
    vector<BigInteger> calList;
    string newline;
    bool cnt;

    getline(cin,line);

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
            cal.pop_back();
            BigInteger number1 = cal.back();
            cal.pop_back();

            switch(it){
                case '+':
                cal.push_back(number1+number2);
                // cout<<(number1+number2).getNum()<<endl;
                    break;
                // case '-':
                //     answer = (number1)-(number2);
                //     break;
                case '*':
                cal.push_back(number1*number2);
                // cout<<(number1*number2).getNum()<<endl;
                //     break;
                // case '/':
                //     answer = (number1)/(number2);
                //     break;
            }
        }

    }
    cout<<cal[0].getNum()<<endl;



}