#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

vector<double> cal;
    string postfix ="";
    int howMany =0;
    string wildcard;
    string wildcardOperator;
    bool addClose = false;
    string temp = "";
    string temp2 = "";
    string rawData="";
    string inputData ="";
    string val = "";
    string process = "";
    vector<string> tempCal;
    double result;

int ord(char op){  // ascii  40 (, 41 ) ,42 * , 43 +, 45 - , 47 /
    if(op==40)return 0;
    if(op==42 || op==47) return 2;
    if(op==43 || op==45) return 1;

    return 2;
}
int ord(string op){ // for wildcard order
    return 2;
}

string unaryToBinary(string &rawData){

    inputData = "";
    for(auto &it:rawData){
        if((it == '-') && (!inputData.empty()) && (inputData.back() =='(') ){
            inputData +="(0";
            inputData += it;
            addClose = true;
        }
        else if((it == '-') && (!inputData.empty()) && (inputData.back()=='*')){
            inputData +="(0-1)*";
        }
        else if((it == '-') && (!inputData.empty()) && (inputData.back() =='/')){
            inputData +="(0-1)/";

        }
        else if((it == '-') && (inputData.empty())){
            inputData +="(0";
            inputData += it;
            addClose = true;
        }
        else{
            if((it=='+'||it=='*'||it=='/'||it=='-') &&(it != '(') && (addClose==true)){
                inputData += ')';

                addClose = false;
            }
            else if((it=='(') && (addClose==true)){
                inputData += "1)*";
                addClose = false;
            }
                inputData += it;
        }

    }
    return inputData;
}



    // cout<<inputData<<endl;

// postfix change
string infixToPostfix(string &inputData){


    for(auto &it: inputData){
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
                default:
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


    // for(unsigned int i=0; i!=temp.size() ; i++){
    //     if((!isdigit(temp[i])) || temp[i] =='+'
    // }


    return temp;
}

// double wildcardCal(double number1, double number2, char op){
//     string tempOperLine="";
//     string tempOperChanged ="";
//     for(unsigned int i =0; i!=wildcardVec.size(): i++){
//         if(op = wildcardVec[i][0]){
//             tempOperLine = wildcardVec[i][1];
//         }
//     tempOperUnaryToBinary = unaryToBinary(tempOperLine)
//     }
//     for (auto &it :tempOperUnaryToBinary){
//         if(&it =='A'){
//             tempOperChanged+=
//         }

//     }



// }

string eraseWildcard(string &rawData){
    char a;
    char back;
    char front;
    string back_str;
    string front_str;
    inputData = unaryToBinary(rawData);
    for(unsigned int i = 0 ; i!=inputData.size(); i++){
        a=inputData[i]
        if((!isdigit(a))&& (a!='+')&&(a!='-')&&(a!='*')&&(a!='/')&&(a!='(')&&(a!=')'))
            for(unsigned int j =0; i!=wildcardVec.size(): i++){
                if(a = wildcardVec[j][0]){
                    if(isdigit(tempOperLine.back)
                        back = tempOperLine.back;
                        tempOperLine.pop_back
                    }
                    else if(tempOperLine.back)

                    tempOperLine = wildcardVec[j][1];
                }
        else{
            tempOperLine+=a;
        }
    }




}


int main(void){


    cin>>howMany;

    vector<vector<string> > wildcardVec;

    for(unsigned int i = 0 ; i != howMany; i++){
        cin>>wildcard;
        cin>>wildcardOperator;
        wildcardVec.push_back(vector<string> (1,wildcard));
        wildcardVec[i].push_back(wildcardOperator);

        // if(i!=0){
        //     for(unsigned int j = i-1; j!=-1; j--){
        //         for(unsigned int k = 0; k!=wildcardVec[i][1].size(); k++){
        //             if(true){
        //             // tempCal.push_back(wildcardVec[i][1][k]);
        //             }
        //             if(string(1,wildcardVec[i][1][k])==wildcardVec[j][0]){
        //                 temp.pop_back();
        //                 temp.pop_back();
        //                 temp += ('(' +wildcardVec[j][1]+')') ;
        //                 k++;
        //             }
        //         }

                // cout<<temp<<endl;
        //         wildcardVec[i][1] = temp;
        //         temp ="";
        //         }
        // }


    }



    for(unsigned int i =0; i!=wildcardVec.size();i++){
        cout<<wildcardVec[i][0]<<" "<<wildcardVec[i][1]<<ord(wildcardVec[i][0])<<endl;
    }


    // assert(0);

    cin>>rawData;


temp = infixToPostfix(inputData);


// postfixculator starts

    for(auto &it: temp){
        if(isdigit(it)){
            process += it;
        }
        else if(isspace(it)){
            if(!process.empty()){
                double push;
                push = stoi(process);
                cal.push_back(push);
                process ="";
                }
            }
        else{
            double number1;
            double number2;
            double answer;
            number2= cal.back();
            // cout<<"number2 :"<< number2<<endl;
            cal.pop_back();
            number1 = cal.back();
            // cout<<number1<<endl;
            cal.pop_back();


            // cout<<"number1 :"<< number1<<endl;

            switch(it){
                case '+':
                    answer = (number1)+(number2);
                    break;
                case '-':
                    answer = (number1)-(number2);
                    break;
                case '*':
                    answer = (number1)*(number2);
                    break;
                case '/':
                    answer = (number1)/(number2);
                    break;
                default:
                    answer = wildcardCal(number1, number2, it)

            }
            // cout<<"answer :"<< answer<<endl;

            cal.push_back(answer);
            // cout<<cal[0]<<endl;
        }

    }
    // cout<<cal[0]<<endl;
    result = cal[0];
    cout.precision(3);
    cout<<fixed<<result<<endl;

    return 0;
}
