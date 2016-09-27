#include <iostream>
#include <string>
#include <vector>


using namespace std;

int order(int op){  // ascii  40 (, 41 ) ,42 * , 43 +, 45 - , 47 /
	if(op==40)return 0;
	if(op==42 || op==47) return 2;
	if(op==43 || op==45) return 1;

	return 0;
}

int main(void){

	vector<char> postfix;
	vector<double> cal;
	int wildcard;
	bool addClose = false;
	string temp = "";
	string rawData="";
	string inputData ="";
	string val = "";
	string process = "";

	double result;
	cin>>wildcard;
	cin>>rawData;

	for(auto &it:rawData){
		if((it == '-') && (!inputData.empty()) && (inputData.back() =='(') ){
			inputData +="(0";
			inputData += it;
			addClose = true;
		}
		else if((it == '-') && (inputData.empty())){
			inputData +="(0";
			inputData += it;
			addClose = true;
		}
		else{
			if((!isdigit(it)) && (addClose==true)){
				inputData += ')';

				addClose = false;
			}
				inputData += it;
		}

	}



	// cout<<inputData<<endl;

// postfix change
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
				case '+': case '-': case '*': case '/' :
					if(!postfix.empty() && postfix.back()!='('){
						while(order(postfix.back())>=order(it)){
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

	//print test
	// cout<<temp<<endl;
	// for(int i=0; i!=postfix.size();i++){
	// 	cout<<postfix[i]<<endl;
	// }


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