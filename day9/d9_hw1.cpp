#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <assert.h>
using namespace std;
	string name;

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

	// void setWitdh(double w){
	// 	Width = w;
	// }
	// void setHeight(double h){
	// 	Height = h;
	// }
	// void setOffsetLeft(double l){
	// 	OffsetLeft = l;
	// }
	// void setOffsetTop(double t){
	// 	OffsetTop = t;
	// }

} ;
class Panel : public FrameworkElement{
public:
	void Add(FrameworkElement *child){
		Children.push_back(child);
	}

	FrameworkElement* Find(string name){
		for(auto &it:Children){
			if(it->Name==name){
				return it;
			}
			else{
				return dynamic_cast<Panel*>(it)->Find(name);
			}
		}
		return nullptr;

	}	
protected:
	vector<FrameworkElement*> Children;

};
class Grid : public Panel{
private:
	int sum(vector<int> vec){
		int sum =0;
		for(auto &it:vec){
			sum+=it;
		}
		return sum;
	}
public:
	vector<int> Cols{1};
	vector<int> Rows{1};

	void UpdateLayout(){
		cout<<"size of Children : "<<Children.size()<<endl;
		for(auto &it:Children){

			double top_ratio=0;
			double left_ratio=0;
			int pcTot = sum(Cols);
			int prTot = sum(Rows);
			int addTop = 0;
			int addLeft = 0;
			for(int i=0; i<GridCol-1;i++){
				addLeft+=(Cols[i])/(double)pcTot*(Width);
			}
			// cout<<addLeft<<endl;
			for(int i=0; i<GridRow-1;i++){
				addTop+=(Rows[i])*(Height)/(double)prTot;
			}
			left_ratio = Cols[GridCol-1]/(double)pcTot;
			cout<<Rows[GridRow-1]<<endl;
			cout<<pcTot<<endl;
			cout<<prTot<<endl;


			top_ratio = Rows[GridRow-1]/(double)prTot;

			it->OffsetTop =OffsetTop+addTop;
			it->OffsetLeft=OffsetLeft+addLeft;
			it->Height = Height*(top_ratio);
			it->Width = Width*(left_ratio);

			it->UpdateLayout();
		}
		return;

	}
	Grid(string n,vector<int> cs,vector<int> rs,int pc, int pr){
		Name = n;
		GridCol = pc;
		GridRow = pr;
		if(cs.size()!=0) Cols = cs;
		if(rs.size()!=0) Rows = rs;

	}
	Grid()=default;
	Grid(string n,vector<int> cs,vector<int> rs){
		Name = n;
		if(cs.size()!=0) Cols = cs;
		if(rs.size()!=0) Rows = rs;
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
	vector<Grid> grid_vec;
	string line;
	// string name;
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
				if(pName=="root_grid"){
					tempParent=&rootGrid;
				}
				grid_vec.push_back(tempGrid);
				tempParent->Add(dynamic_cast<FrameworkElement*>(&grid_vec.back()));;

			}

			// cout<<"size of rootGrid childeren : "<<rootGrid.Children.size()<<endl;
			rowVec.clear();
			colVec.clear();
			pCol = pRow = 1;

		}//if for Grid
		else{


			ss>>command;//discard Name stirng;
			ss>>name;//Name
			
			rootGrid.UpdateLayout();

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
				// assert(v0);

				// if(it==nullptr) continue;
				if(!pName.compare("root_grid")){
					it = &rootGrid;
				}

					cout<<"pName : "<<pName<<endl;
					cout<<"value of it : "<<it->Name<<endl;
			Rectangle tempRect = Rectangle(name,color,pCol,pRow);

			int pcTot = 0;
			for(auto &it2:it->Cols){
				pcTot+=it2;
			}
			int prTot = 0;
			for(auto &it2:it->Rows){
				prTot+=it2;
			}


			double addLeft=0;
			double addTop=0;
			cout<<pCol<<endl;
			cout<<pRow<<endl;
			cout<<it->Cols.size()<<endl;
			cout<<it->Rows[0]<<endl;

			double left_ratio = it->Cols[pCol-1]/(double)pcTot;
			double top_ratio = it->Rows[pRow-1]/(double)prTot;


			// cout<<pcTot<<it->Cols[0]<<endl;
			// cout<<it->Width<<endl;
			for(int i=0; i<pCol-1;i++){
				addLeft+=(it->Cols[i])/(double)pcTot*(it->Width);
			}


			for(int i=0; i<pRow-1;i++){
				addTop+=(it->Rows[i])/(double)prTot*(it->Height);
			}
			cout<<it->GridCol<<endl;
			cout<<"pc tot : "<<pcTot<<endl;
			cout<<"pr tot : "<<prTot<<endl;
			cout<<"left_ratio : "<<left_ratio<<endl;
			cout<<"top_ratio : "<<top_ratio<<endl;
			tempRect.OffsetLeft =it->OffsetLeft+addLeft;
			tempRect.OffsetTop = it->OffsetTop+addTop;
			tempRect.Width = it->Width*(left_ratio);
			tempRect.Height = it->Height*(top_ratio);



			pCol = pRow = 1;
			rect_vec.push_back(tempRect);
		}



		// cout<<subCommand2<<endl;
			// if(subCommand2.compare("end")) break;

}//for loop with input Number;

for(auto it:rect_vec){
	cout<<it.Name<<" "<<it.Fill<<" "<<it.OffsetLeft<<" "<<it.OffsetTop<<" "<<it.Width<<" "<<it.Height<<endl;
}
for(auto it:grid_vec){
	cout<<it.Name<<" "<<it.OffsetLeft<<" "<<it.OffsetTop<<" "<<it.Width<<" "<<it.Height<<endl;

}


	return 0;

}
