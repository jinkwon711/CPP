#include <iostream>
#include <string>
#include <map>
#include <limits>
#include <functional>

using namespace std;

class Value {
private:
	int value;
	static int count;

public:

	Value() {
		value = pseudoRandom();
		count++;
	}

	int pseudoRandom() {
		return (count * 42) * (count * 42) / 108;
	}
	friend Value operator+(const Value &i, const Value &i2);
	friend bool operator==(const Value &i, const Value &i2);

	Value& operator++(){
		this->value++;
		return *this;

	}//prefix

	Value& operator++(int){
		Value temp;
		temp.value= this->value;
		this->value++;
		return temp;
	}//postfix

	Value &operator +=(const Value& val){
		this->value= this->value +val.value;
		return *this;
	}
	friend ostream& operator<<(ostream& os,const Value& val);






    /*
        OVERLOAD OPERATORS HERE
        (AS A MEMBER)
    */
};

ostream& operator<<(ostream &os, const Value &val){
	os<< val.value;
	return os;
}

Value operator+(const Value &i,const Value &i2 ){
	Value sum ;
	sum.value= i.value+ i2.value;
	return sum;
}

bool operator==(const Value &i, const Value &i2){
	if(i.value==i2.value) return true;
	else return false;
}
/*
    OR HERE
    (AS A NON-MEMBER)
*/

bool validate(const map<string, Value> &vMap, string A) {
	if (vMap.find(A) == vMap.end()) return false;
	else return true;
}

bool validate(const map<string, Value> &vMap, string A, string B) {
	if (vMap.find(A) == vMap.end()) return false;
	else if (vMap.find(B) == vMap.end()) return false;
	else return true;
}

int Value::count = 1;

int main() {
	map<string, Value> valueMap;
	string command, name;
	string left, right;

	map<string, function<Value(Value&, Value&)>> binops = {
		{ "add", [](Value& leftValue, Value& rightValue)->Value { return leftValue + rightValue; } },
		{ "addassign", [](Value& leftValue, Value& rightValue)->Value { return leftValue += rightValue; } }
	};

	map<string, function<bool(Value&, Value&)>> relops = {
		{ "equal", [](Value& leftValue, Value& rightValue)->bool { return leftValue == rightValue; } }
	};

	map<string, function<Value(Value&)>> unops = {
		{ "incpre", [](Value& value)->Value { return ++value; } },
		{ "incpost", [](Value& value)->Value { return value++; } },
	};

	while (true) {
		cin >> command;

		if (command == "new") {
			cin >> name;
			valueMap.insert({ name, Value() });
		}

		else if (command == "add" || command == "addassign") {
			cin >> left >> right;
			if (validate(valueMap, left, right))
				cout << binops[command](valueMap[left], valueMap[right]) << endl;
			else
				cout << "undefined" << endl;
		}

		else if (command == "equal") {
			cin >> left >> right;
			if (validate(valueMap, left, right))
				cout << relops[command](valueMap[left], valueMap[right]) << endl;
			else
				cout << "undefined" << endl;
		}

		else if (command == "incpre" || command == "incpost") {
			cin >> name;
			if (validate(valueMap, name))
				cout << unops[command](valueMap[name]) << endl;
			else
				cout << "undefined" << endl;
		}

		else if (command == "print") {
			cin >> name;
			if (validate(valueMap, name))
				cout << valueMap[name] << endl;
			else
				cout << "undefined" << endl;
		}

		else if (command == "printAll") {
			for (auto e : valueMap) {
				cout << e.first << " : " << e.second << endl;
			}
		}

		else if (command == "end") {
			break;
		}

		else {
			cout << "Command is not defined" << endl;
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return 0;
}
