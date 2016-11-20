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
  vector<pair<string,string> > cattr;
  // vector<pair<string,string> > dAttr; 
  vector<pair<string,string> > tattr;
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
  vector<SVG *> parentSvg;
  Selection(SVG* queryCurrSVG){
    selectedSvg.push_back(queryCurrSVG);
    // parentSvg.push_back(queryCurrSVG);

  }

  void append(string queryName){
    parentSvg.push_back(selectedSvg[0]);// push parent;
    SVG* newSVG = new SVG(queryName);//  create new SVG object
    selectedSvg[0]->children.push_back(newSVG);// put new obj to current svg;
    selectedSvg.clear();
    selectedSvg.push_back(newSVG);// put new SVG as selected
  }
  void append(string queryName,vector<string>* queryData){
    SVG* newSVG = new SVG(queryName);
    newSVG->data = *queryData;
    parentSvg.back()->children.push_back(newSVG);
    selectedSvg.push_back(newSVG);
  }


  void select(string queryName){
    parentSvg.push_back(selectedSvg[0]);
    selectedSvg.clear();
    for(auto &it:parentSvg.back()->children){
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
    // if(parentSvg.back()->name==root_svg);
    selectedSvg.clear();
    selectedSvg.push_back(parentSvg.back());
    parentSvg.pop_back();
  }
  // void svgNotExist(){
  // }

  void enter(int csvIdx,vector<CVS*> cvs_vec){
    sort(cvs_vec[csvIdx]->data.begin(),cvs_vec[csvIdx]->data.end(),
      [](vector<string>* left,vector<string> *right){return *left<*right;});
    vector<SVG *> tempSvg;
    tempSvg = selectedSvg;
    selectedSvg.clear();
    
    // for(auto &item:cvs_vec[csvIdx]->data){
    //   for(auto &it:*item){
    //       cout<<it<<"  ";
    //   }
    //   cout<<endl;
    // } // sorting check;
    int exist;
    for(auto &csvItem:cvs_vec[csvIdx]->data){
      exist = 0;
      // cout<<"not hi"<<endl;
      for(auto &selectedItem:tempSvg){
        if((*csvItem)[0]==selectedItem->name)
          exist =1;
          break;
      }
      if(exist==0){
        // cout<<"hi"<<endl;
        append(lastQueryName,csvItem);
      }
    }
       
  }

  void update(int csvIdx,vector<CVS*> cvs_vec){
    sort(cvs_vec[csvIdx]->data.begin(),cvs_vec[csvIdx]->data.end(),
      [](vector<string>* left,vector<string> *right){return *left<*right;});
    vector<SVG *> tempSvg;
    tempSvg = selectedSvg;
    selectedSvg.clear();
    for(auto &csvItem:cvs_vec[csvIdx]->data){
      for(int i=0; i!=tempSvg.size();i++){
        if((*csvItem)[0]==tempSvg[i]->data[0]){
          tempSvg.erase(tempSvg.begin()+i);
          append(lastQueryName,csvItem);
          i--;
          break;
        }
      }
    }
  }
  void exit(int csvIdx,vector<CVS*> cvs_vec){
    for(auto &csvItem:cvs_vec[csvIdx]->data){
      for(int i=0; i!=selectedSvg.size();i++){
        if((*csvItem)[0]==selectedSvg[i]->data[0]){
          selectedSvg.erase(selectedSvg.begin()+i);
          i--;
          break;
        }
      }
    }
    sort(cvs_vec[csvIdx]->data.begin(),cvs_vec[csvIdx]->data.end(),
      [](vector<string>* left,vector<string> *right){return *left<*right;});
  }



  void cattr(string attrName, string attrValue){
    for(auto &svgItem:selectedSvg){
      svgItem->cattr.
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
Selection* selection = new Selection(root_svg);


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


selection->select("rect");
selection->enter(0,cvs_vec);
cout<<"---------------------select & enter check-----------"<<endl;
for(auto &it:selection->selectedSvg){
  for(auto& item:it->data){
        cout<<item<<"  ";
  }
  cout<<endl;
}
cout<<"---------------------select & enter check-----------"<<endl;
selection->update(1,cvs_vec);
cout<<"---------------------select & update check-----------"<<endl;
for(auto &it:selection->selectedSvg){
  for(auto& item:it->data){
        cout<<item<<"  ";
  }
  cout<<endl;
}
cout<<"---------------------select & update check-----------"<<endl;
  
selection->exit(1,cvs_vec); 

cout<<"---------------------select & exit check-----------"<<endl;
for(auto &it:selection->selectedSvg){
  for(auto& item:it->data){
        cout<<item<<"  ";
  }
  cout<<endl;
}
cout<<"---------------------select & exit check-----------"<<endl;





  delete(root_svg);
  delete(selection);
  return 0;
}
