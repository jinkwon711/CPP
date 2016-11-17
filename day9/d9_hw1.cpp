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

} ;
class Panel : public FrameworkElement{
public:
	void Add(FrameworkElement *child){
		Children.push_back(child);
		return ;
	}

	FrameworkElement* Find(string name){
		for(auto &it:Children){
			if(it->Name==name){
				return it;
			}
			else{
				if(nullptr!=dynamic_cast<Panel*>(it)->Find(name)){
					return dynamic_cast<Panel*>(it)->Find(name);
				}
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
	// void FreeMem(){
	// 	for(auto &it:Children){
	// 		delete this;
	// 		it->UpdateLayout();
	// 	}
	// }


public:
	vector<int> Cols{1};
	vector<int> Rows{1};

	void UpdateLayout(){
		for(int i=0; i!=Children.size();i++){
			// cout<<Children[i]->Name<<endl;
		}

		// cout<<"부모이름 : "<<Name<<endl;
		for(auto &it:Children){
			// cout<<"자식이름 : "<<it->Name<<endl;

			double top_ratio=0;
			double left_ratio=0;
			int pcTot = sum(Cols);
			int prTot = sum(Rows);
			// cout<<pcTot<< "  " <<prTot<<endl;

			double addTop = 0;
			double addLeft = 0;
			for(int i=0; i<it->GridCol-1;i++){
				addLeft+=(Cols[i])/(double)pcTot*(this->Width);
			}
			
			for(int i=0; i<it->GridRow-1;i++){

				addTop+=(Rows[i])*(this->Height)/(double)prTot;
			}
			left_ratio = Cols[it->GridCol-1]/(double)pcTot;

			top_ratio = Rows[it->GridRow-1]/(double)prTot;

			it->OffsetTop =this->OffsetTop+addTop;
			it->OffsetLeft=this->OffsetLeft+addLeft;
			it->Height = this->Height*(top_ratio);
			it->Width = this->Width*(left_ratio);
			// cout<<"OffsetLeft"<<it->OffsetLeft<<endl;
			// cout<<"OffsetTop"<<it->OffsetTop<<endl;
			// cout<<"Height"<<it->Height<<endl;
			// cout<<"Width"<<it->Width<<endl;

			// dynamic_cast<Grid*>(it)->UpdateLayout();
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
	Grid *rootGrid;
	vector<Rectangle> rect_vec;
	int index=0;
	// vector<Grid> grid_vec;
	Grid* GridArr[250];
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
	cols1 = cols2 = pCol = rows1=rows2=pRow=1;
	istringstream ss(line);
	ss>>command;
		if(command=="Grid"){
			ss>>command;//discard Name stirng;
			ss>>name;//Name

				//subcommand is name, subcommand2 = Col or Rows or Parent;
			while(ss>>subCommand2){
				// switch(subCommand2){
				if(!subCommand2.compare("Cols")){
					ss>>cols1;
					for(int i=0;i!=cols1;i++){
						ss>>cols2;
						colVec.push_back(cols2);
					}
					ss>>subCommand2;
				}
				if(!subCommand2.compare("Rows")){
					ss>>rows1;

					for(int i=0;i!=rows1;i++){
						ss>>rows2;
						rowVec.push_back(rows2);
					}
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
			if(name=="root_grid"){
				rootGrid = new Grid(name,colVec,rowVec);
				// grid_vec.push_back(*rootGrid);
			}
			else{
				Grid *tempGrid;
				tempGrid = new Grid(name,colVec,rowVec,pCol,pRow);
				Grid *tempParent=dynamic_cast<Grid*>(rootGrid->Find(pName));
				if(pName=="root_grid"){
					tempParent=rootGrid;
				}
				GridArr[index]=tempGrid;
				// tempParent->Add(dynamic_cast<FrameworkElement*>(tempGrid));
				tempParent->Add(dynamic_cast<FrameworkElement*>(GridArr[index]));
				index++;

			}

			rowVec.clear();
			colVec.clear();
			rootGrid->UpdateLayout();




		}//if for Grid
		else{
			cols1 = cols2 = pCol = rows1=rows2=pRow=1;
			ss>>command;//discard Name stirng;
			ss>>name;//Name

				//subcommand is name, subcommand2 = Col or Rows or Parent;
			while(ss>>subCommand2){
				// switch(subCommand2){
				if(!subCommand2.compare("Cols")){
					ss>>cols1;
					for(int i=0;i!=cols1;i++){
						ss>>cols2;
						colVec.push_back(cols2);
					}
					ss>>subCommand2;
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
				// cout<<pName<<endl;
				Grid *it = dynamic_cast<Grid*>(rootGrid->Find(pName));
				// cout<<it<<endl;

				// if(it==nullptr) continue;
				if(!pName.compare("root_grid")){
					it = rootGrid;
				}


					// assert(name!="yellow_rect");
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

			double left_ratio = it->Cols[pCol-1]/(double)pcTot;
			double top_ratio = it->Rows[pRow-1]/(double)prTot;


			for(int i=0; i<pCol-1;i++){
				addLeft+=(it->Cols[i])/(double)pcTot*(it->Width);
			}


			for(int i=0; i<pRow-1;i++){
				addTop+=(it->Rows[i])/(double)prTot*(it->Height);
			}
			tempRect.OffsetLeft =it->OffsetLeft+addLeft;
			tempRect.OffsetTop = it->OffsetTop+addTop;
			tempRect.Width = it->Width*(left_ratio);
			tempRect.Height = it->Height*(top_ratio);



			rect_vec.push_back(tempRect);
		}



			// if(subCommand2.compare("end")) break;

}//for loop with input Number;
			// cout<<grid_vec[0].Children[0]->Name<<endl;


for(auto it:rect_vec){
	cout.precision(2);
		cout<<fixed<<it.Name<<" "<<it.Fill<<" "<<it.OffsetLeft<<" "<<it.OffsetTop<<" "<<it.Width<<" "<<it.Height<<endl;
}


for(int i=0; i!=index;i++){
	cout<<GridArr[i]->Name<<endl;
}

for(int i=0; i!=index;i++){
	delete GridArr[i];
}




	return 0;

}
