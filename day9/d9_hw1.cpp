#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;


class UIElement{
public:
	string Name;
	void setName(string n){
		Name = n;
	}
};
class FrameworkElement:public UIElement{
public:
	double Width;
	double Height;
	double OffsetLeft;
	double OffsetTop;
	int Gridcol = 1;
	int GridRow = 1;
	virtual void UpdateLayout(){}

	void setWitdh(double w){
		Width = w;
	}
	void setHeight(double h){
		Height = h;
	}
	void setOffsetLeft(double l){
		OffsetLeft = l;
	}
	void setOffsetTop(double t){
		OffsetTop = t;
	}
} ;
class Panel : public FrameworkElement{
public:
	void Add(FrameworkElement *child);
	FrameworkElement Find(string name);
protected:
	vector<FrameworkElement*> Children;
};
class Grid : public Panel{
public:
	vector<int> Cols{1};
	vector<int> Rows{1};
	void UpdateLayout();
	// Grid(string n, string f, int c int r,vector<int> cs,vector<int> rs):Name(n),Fill(f),Gridcol(c),GridRow(r),Cols(cs),Rows(rs){}
	Grid(string n):Name(n){
		Width=100;
		Height=100;
		OffsetTop=0;
		OffsetLeft=0;
	}
};
class Shapes:public FrameworkElement{

};
class Rectangle:public Shapes{
public:
	string Fill;
	// Rectangle(string n, string f, int c int r):Name(n),Fill(f),Gridcol(c),GridRow(r){}
};

int main(){
	string line;
	string name;
	string subCommand;
	string subCommand2;
	string subCommand3;
	string pName;
	vector<int> colVec;
	vector<int> rowVec;
	int cols1,cols2,pCol;
	int rows1,rows2,pRow;

	int N;
	cin>>N;//2<=N<=200

	//test

	for(int i=0; i!=N; i++){
	getline(cin,line);
	istringstream ss(line);
	while(ss>>command){
		if(command=="Grid"){
			ss>>command;//discard Name stirng;
			ss>>name;//Name
			if(Name=="root_grid")
				Grid rootGrid = Grid(name);
			}
			else{
				Grid tempGrid = Grid(name);
				//subcommand is name, subcommand2 = Col or Rows or Parent;
				while(ss>>subCommand2){
					switch(subCommand2){
						case "Cols":
							ss>>cols1;
							for(int i=0;i!=cols1;i++){
								ss>>cols2;
								colVec.push_back(cols2);
							}
							ss>subCommand2;
							break;
						case "Rows":
							ss>>rows1;
							for(int i=0;i!=rows1;i++){
								ss>>rows2;
								rowVec.push_back(rows2);
							}
							ss>>subCommand2;
							break;
						case "Parent":
							ss>>pName;
							while(ss>>subCommand3){
								switch(subCommand3){
									case "Col":
										ss>>pCol;
										break;
									case "Row":
										ss>>pRow;
										break;
									case "end":
										break;
								}
							
							}
					}
				}
			}

		}
		// else if(command=="Rectangle")
	}	






	return 0;
}		