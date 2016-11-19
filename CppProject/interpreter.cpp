#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;

class CVS{
public:
  vector<vector<string>* > field;
  vector<vector<string>* > type;
  vector<vector<string>* > data;
};
class SVG{
public:
  string name;
  vector<string> data;
  vector<pair<string,string> > cAttr;
  // vector<pair<string,string> > dAttr; 
  vector<pair<string,string> > tAttr;
  vector<string> originalData;
  vector<string> changedData;
  vector<SVG *> children;

  SVG(string queryName):name(queryName){};

};

class Selection{
public:
  string lastQueryName;

  // vector<SVG *> allSvg;
  vector<SVG *> selectedSvg;
  vector<SVG *> currSVG;
  Selection(SVG* queryCurrSVG){
    currSVG.push_back(queryCurrSVG);
  }

  void append(string queryName){
    SVG* newSVG = new SVG(queryName);
    currSVG.back()->children.push_back(newSVG);
  }
  void append(string queryName,vector<string>* queryData){
    SVG* newSVG = new SVG(queryName);
    newSVG->data = *queryData;
    currSVG.back()->children.push_back(newSVG);
  }


  void select(string queryName){
    selectedSvg.clear();
    for(auto &it:currSVG.back()->children){
      if(it->name == queryName )
        selectedSvg.push_back(it);
    }
    lastQueryName = queryName;
  }

  void remove(){
    for(auto &it:selectedSvg){
      delete(it);
    }
    end();
  }

  void end(){//main안에서 root가 셀렉된경우 함수 종료시키자.
    // if(currSVG.back()->name==root_svg);
    selectedSvg.clear();
    selectedSvg.push_back(currSVG.back());
    currSVG.pop_back();
  }
  // void svgNotExist(){
  // }

  void enter(int csvIdx,vector<CVS*> cvs_vec){
    sort(cvs_vec[csvIdx]->data.begin(),cvs_vec[csvIdx]->data.end(),
      [](vector<string>* left,vector<string> *right){return *left<*right;});
    for(auto &item:cvs_vec[csvIdx]->data){
      for(auto &it:*item){
          cout<<it<<"  ";
      }
      cout<<endl;
    } // sorting check;
    int exist;
    for(auto &csvItem:cvs_vec[csvIdx]->data){
      exist = 0;
      cout<<"not hi"<<endl;
      for(auto &selectedItem:selectedSvg){
        if((*csvItem)[0]==selectedItem->name)
          exist =1;
          break;
      }
      if(exist==0){
        cout<<"hi"<<endl;
        append(lastQueryName,csvItem);
      }
    }
  }
};




int main(int argc,char **argv){
string line;
vector<CVS*> cvs_vec;
// vector<string> item;
// vector<vector<string> > csvItem;
// vector<vector<vector<string> > >totalCsvItem;
SVG* root_svg = new SVG("html");
Selection* root_selection = new Selection(root_svg);


//file stream to vector.
int j=0;
  for(int i=1; i<argc;i++){
  CVS *cvs = new CVS();
    ifstream inFile(argv[i]);
    int isfirst=1;
    while(!inFile.eof()){
      getline(inFile,line);//getline
      if(line=="") break;
      string tempString="";
      vector<string> *item = new vector<string>();
      for(int i=0; i!=line.length(); i++){
        if(line[i]==','||line[i]=='\0'){
          item->push_back(tempString);
          tempString="";
        }
        else tempString+=line[i];//split by ','
      }
      item->push_back(tempString);

      if(isfirst==1){

        cvs->field.push_back(item);
        isfirst++;
      }else if(isfirst==2){
        isfirst++;
        cvs->type.push_back(item);
      }else{
        cout<<(*item)[0]<<endl;
        cvs->data.push_back(item);        
      }
    }
    cvs_vec.push_back(cvs);
  }

  // cout<<"---------------cvs io check----------------"<<endl;

  // for(auto &cvsObj:cvs_vec){
  //   for(auto &it:*cvsObj->field[0]){
  //     cout<<it<<"  ";
  //   }
  //   cout<<endl;
  //   for(auto &it:*cvsObj->type[0]){
  //     cout<<it<<"  ";
  //   }
  //   cout<<endl;
  
  //   for(auto &item:cvsObj->data){
  //     for(auto &it:*item){
  //         cout<<it<<"  ";
  //     }
  //     cout<<endl;
  //   }
  // }
  // cout<<"---------------cvs i/o check end-------------"<<endl;



  root_selection->enter(0,cvs_vec);


root_selection->select("rect");
for(auto &it:root_selection->selectedSvg){
  for(auto& item:it->data){
   for(auto &it:item){
        cout<<it<<"  ";
    }
    cout<<endl;
  }

}
  
  delete(root_svg);
  delete(root_selection);
  return 0;
}
