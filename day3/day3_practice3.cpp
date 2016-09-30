#include <iostream>
#include <vector>

using namespace std;
class Movie {
public:
	Movie() = default;
	Movie(int a,string b, vector<string> c): year(a), title(b), actorList(c){}

	int getYear(){
		return year;
	}
	string getName(){
		return title;
	}
	string getMainActor(){
		return actorList[0];
	}
	string getActor(int index){
		return actorList[index-1];
	}
private:
	int year = 1900;
	string title ="Unknown";
	vector<string> actorList;



};
int main(void) {
Movie unknown;
cout << unknown.getYear() << endl; // 1900
cout << unknown.getName() << endl; // Unknown
vector<string> actors {"Uma Thurman", "Lucy Liu", "David Carradine"};
Movie killbill(2003, "Kill Bill", actors);
cout << killbill.getYear() << endl; // 2003
cout << killbill.getName() << endl; // Kill Bill
cout << killbill.getMainActor() << endl; // Uma Thurman
cout << killbill.getActor(3) << endl; // David Carradine
}
