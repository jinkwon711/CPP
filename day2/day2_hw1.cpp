#include <iostream>
#include <string>
#include <vector> 


using namespace std;

int order(int op){  // ascii  40 (, 41 ) ,42 * , 43 +, 45 - , 47 /
	if(op==40)return 0;
	if(op==42 || op==47) return 2;
	if(op==43 || op==45) return 1;
	if(op==41) return -1;
} 

int main(void){

	vector<char> cal;
	vector<int> result;

	string temp = "";
	string inputData ="";
	cin>>inputData;


	for(auto &it: inputData){
		if (isdigit(it)){
			temp += it;
		}
		else{
			switch(it){
				case '(' :
					cal.push_back(it);
					break;
				case ')' :
					while(cal.back() != '('){
						temp += cal.back();
						cal.pop_back();				
					}
					cal.pop_back(); //discard '('
					break;
				case '+': case '-': 
					if(!cal.empty() && cal.back()!='('){
						while(order(cal.back())>=order(it)){
							
							temp+=cal.back();
							cal.pop_back();
						}
					}
					cal.push_back(it);
					break;
			}
		
		}
	} 
	for(auto &it : cal){
		temp +=it;
	}




	cout<<temp<<endl;


	for(int i=0; i!=cal.size();i++){
		cout<<cal[i]<<endl;	
	}






}