#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <assert.h>
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
	int GridCol = 1;
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
	void Add(FrameworkElement *child){
		Children.push_back(child);
	}
	FrameworkElement* Find(string name){
		for(auto it:Children){
			cout<<"inside Find"<<endl;
			return dynamic_cast<Panel*>(it)->Find(name);
			if(it->Name==name){
				return it;
			}
		}
		return nullptr;
	}
protected:
	vector<FrameworkElement*> Children;
};
class Grid : public Panel{
public:
	vector<int> Cols{1};
	vector<int> Rows{1};
	void UpdateLayout(){
		return;
	}
	Grid(string n,vector<int> cs,vector<int> rs,int pc, int pr){
		Name = n;
		GridCol = pc;
		GridRow = pr;
		Cols = cs;
		Rows = rs;
	}
	Grid()=default;
	Grid(string n,vector<int> cs,vector<int> rs){
		Name = n;
		Cols = cs;
		Rows = rs;
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
	Rectangle(string n){Name = n;}
	Rectangle(string n, string f, int c, int r){
		Name = n;
		Fill = f;
		GridCol = c;
		GridRow = r;
	}
};

int main(){
	Grid rootGrid;
	vector<Rectangle> rect_vec;
	string line;
	string name;
	string command;
	string subCommand2;
	string subCommand3;
	string pName;
	string color;
	vector<int> colVec;
	vector<int> rowVec;
	int cols1,cols2,pCol;
	int rows1,rows2,pRow;
	int N;
	cin>>N;//2<=N<=200
	cin.ignore(256, '\n');


	//test

	for(int i=0; i!=N; i++){
	getline(cin,line);

	istringstream ss(line);
	ss>>command;
		if(command=="Grid"){
			ss>>command;//discard Name stirng;
			ss>>name;//Name
			cout<<"name : "<<name<<endl;

				//subcommand is name, subcommand2 = Col or Rows or Parent;
			while(ss>>subCommand2){
				cout<<"subCommand2 : "<<subCommand2<<endl;
				// switch(subCommand2){
				if(!subCommand2.compare("Cols")){
					cout<<"cols1 : "<<cols1<<endl;
					ss>>cols1;
					for(int i=0;i!=cols1;i++){
						ss>>cols2;
						colVec.push_back(cols2);
					}
					ss>>subCommand2;
					cout<<"subcommand2-2 :"<<subCommand2<<endl;
				}
				if(!subCommand2.compare("Rows")){
					ss>>rows1;
					cout<<"rows1 : "<<rows1<<endl;

					for(int i=0;i!=rows1;i++){
						ss>>rows2;
						rowVec.push_back(rows2);
					}
					ss>>subCommand2;
				}
				if(!subCommand2.compare("Parent")){
					ss>>pName;
					while(ss>>subCommand3){
						if(!subCommand2.compare("Col")){
								ss>>pCol;
						}
						else if(!subCommand2.compare("Row")){
								ss>>pRow;
						}
						else if(!subCommand2.compare("end")){
								break;
						}
					}
				}
			}//second while

			if(name=="root_grid"){
				rootGrid = Grid(name,colVec,rowVec);
			}
			else{
				Grid tempGrid = Grid(name,colVec,rowVec,pCol,pRow);
				Grid *tempParent=dynamic_cast<Grid*>(rootGrid.Find(pName));
				tempParent->Add(dynamic_cast<FrameworkElement*>(&tempGrid));;

			}
			rowVec.clear();
			colVec.clear();
			pCol = pCol = 1;

		}//if for Grid
		else{
			ss>>command;//discard Name stirng;
			ss>>name;//Name
			cout<<"name : "<<name<<endl;
				//subcommand is name, subcommand2 = Col or Rows or Parent;
			while(ss>>subCommand2){
				cout<<"subCommand2 : "<<subCommand2<<endl;
				// switch(subCommand2){
				if(!subCommand2.compare("Cols")){
					cout<<"cols1 : "<<cols1<<endl;
					ss>>cols1;
					for(int i=0;i!=cols1;i++){
						ss>>cols2;
						colVec.push_back(cols2);
					}
					ss>>subCommand2;
					cout<<"subcommand2-2 :"<<subCommand2<<endl;
				}
				if(!subCommand2.compare("Fill")){
					ss>>color;
					ss>>subCommand2;
				}
				if(!subCommand2.compare("Parent")){
					ss>>pName;
					while(ss>>subCommand2){
						if(!subCommand2.compare("Col")){
								ss>>pCol;
						}
						else if(!subCommand2.compare("Row")){
								ss>>pRow;
						}
						else if(!subCommand2.compare("end")){
								break;
						}
					}
				}
			}//second while
				Grid *it = dynamic_cast<Grid*>(rootGrid.Find(pName));

				if(!pName.compare("root_grid")){
					it = &rootGrid;
					}

					cout<<it->Name<<endl;
assert(0);

			Rectangle tempRect = Rectangle(name,color,pCol,pRow);

			int pcTot = it->Cols.size();
			int prTot = it->Rows.size();



			double addLeft=0;
			double addTop=0;

			cout<<pcTot<<it->Cols[0]<<endl;
			cout<<it->Width<<endl;
			for(int i=0; i!=pCol-1;i++){
				addLeft= addLeft+(it->Cols[i])/(double)pcTot*(it->Width);
			}
			cout<<addLeft<<endl;
			for(int i=0; i!=pCol-1;i++){
				addTop+=(it->Cols[i]*it->Height)/prTot;
			}
			tempRect.OffsetLeft =it->OffsetLeft+addLeft;
			tempRect.OffsetTop = it->OffsetTop+addTop;


			pCol = pRow = 1;
			rect_vec.push_back(tempRect);
		}



		// cout<<subCommand2<<endl;
			// if(subCommand2.compare("end")) break;

}//for loop with input Number;

for(auto it:rect_vec){
	cout<<it.Name<<" "<<it.Fill<<" "<<it.OffsetLeft<<" "<<it.OffsetTop<<" "<<it.Width<<" "<<it.Height<<endl;
}


	return 0;

}
