#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
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
  vector<pair<double,double> > tattr;
  vector<string> originalData;
  vector<string> changedData;
  vector<SVG *> children;

  SVG(string queryName):name(queryName){};
  ~SVG(){
    for(auto &it:children){
      delete(it);
    }
  }
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
      for(int i=0; i!=parentSvg.back()->children.size();i++){
        if(parentSvg.back()->children[i]->name==it->name){
          parentSvg.back()->children.erase(parentSvg.back()->children.begin()+i);
          cout<<parentSvg.back()->children[i]->data[0]<<endl;

          i--;
          break;
        }
      }
    }
    for(auto &it:selectedSvg){
      cout<<it->name<<"deleted"<<endl;
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

  void enter(int csvIdx,vector<CVS*> csv_vec){
    sort(csv_vec[csvIdx]->data.begin(),csv_vec[csvIdx]->data.end(),
      [](vector<string>* left,vector<string> *right){return *left<*right;});
    // vector<SVG *> tempSvg;
    // tempSvg = selectedSvg;
    
    // for(auto &item:csv_vec[csvIdx]->data){
    //   for(auto &it:*item){
    //       cout<<it<<"  ";
    //   }
    //   cout<<endl;
    // } // sorting check;
    int exist;
    for(auto &csvItem:csv_vec[csvIdx]->data){
      exist = 0;
      for(auto &selectedItem:selectedSvg){
        if((*csvItem)[0]==selectedItem->data[0]){
          exist =1;
          break;
        }
      }
      if(exist==0){
        append(lastQueryName,csvItem);
      }
    }
       
  }

  void update(int csvIdx,vector<CVS*> csv_vec){
    sort(csv_vec[csvIdx]->data.begin(),csv_vec[csvIdx]->data.end(),
      [](vector<string>* left,vector<string> *right){return *left<*right;});
    vector<SVG *> tempSvg;
    tempSvg = selectedSvg;
    int exist;
    for(int i=0; i!=selectedSvg.size();i++){
      exist=0;
      for(auto &csvItem:csv_vec[csvIdx]->data){
        if((*csvItem)[0]==selectedSvg[i]->data[0]){
          selectedSvg[i]->data = (*csvItem);
          exist = 1;
          break;
        }
      }
      if(exist==0){
          selectedSvg.erase(selectedSvg.begin()+i);
          i--;
      }
    }
  }
  void exit(int csvIdx,vector<CVS*> csv_vec){
    for(auto &csvItem:csv_vec[csvIdx]->data){
      for(int i=0; i!=selectedSvg.size();i++){
        if((*csvItem)[0]==selectedSvg[i]->data[0]){
          selectedSvg.erase(selectedSvg.begin()+i);
          i--;
          break;
        }
      }
    }
    sort(csv_vec[csvIdx]->data.begin(),csv_vec[csvIdx]->data.end(),
      [](vector<string>* left,vector<string> *right){return *left<*right;});
  }



  void cattr(string attrName, string attrValue){
    for(auto &svgItem:selectedSvg){

      // Pair<string,string> tempPair = {attrName,attrValue};
      svgItem->cattr.push_back({attrName,attrValue});
    }
  }
  void tattr(double x_mul,double y_mul){
    int idx=1;
    for(auto &svgItem:selectedSvg){
      // for(int i=1; i<=selectedSvg.size();i++)
      //   if(selectedSvg[i]->name==svgItem->name){
      //     idx=i;
      //   }
        svgItem->tattr.push_back({x_mul*idx,y_mul*idx});
        idx++;
      }
  }
  void dattr(vector<CVS*> csv_vec,string attrName,string valueName,double mul=1.0,double add = 0.0){
    // cout<<attrName<<":"<<valueName<<":"<<mul<<":"<<add<<endl;
    int dataIdx;
    int isString=0;
    // cout<<csv_vec[0]->field[0]->size()<<endl;
    for(int i=0;csv_vec[0]->field[0]->size();i++){
      if((*(csv_vec[0]->field[0]))[i]==valueName){
        dataIdx =i;
        // cout<<"dataindex"<< dataIdx<<endl;
        if((*(csv_vec[0]->type[0]))[i]=="string") isString=1;
        // cout<<"isString"<<endl;
        break;
      }
    }
    // cout<<"after check index"<<endl;
    for(auto &svgItem:selectedSvg){
      int exist =0;
      for(auto &attrItem:svgItem->cattr){
        if(attrItem.first==attrName){
          if(isString){
            attrItem.second = svgItem->data[dataIdx];
          }
          else{
            ostringstream strs;
            strs << stod(svgItem->data[dataIdx])*mul+add ;
            string str = strs.str();
            attrItem.second =str;
          }
          
          exist = 1;
          break;
        }
      }
      if(exist==0){
        if(isString){
          svgItem->cattr.push_back({attrName,svgItem->data[dataIdx]});
        }
        else{
          ostringstream strs;
          strs << stod(svgItem->data[dataIdx])*mul+add ;
          string str = strs.str();
          svgItem->cattr.push_back({attrName,str});
        }
      }    
    }
  }
  void print(SVG* svgRoot,ofstream& outFile){
    outFile<<"<"<<svgRoot->name<<" ";
    for(auto &it:svgRoot->cattr){
      outFile<<it.first<<"="<<"\""<<it.second<<"\""<<" ";
    }
    for(auto &it2:svgRoot->tattr){
      outFile<<"transform=\"translate(";
      outFile<<it2.first<<","<<it2.second<<")\"";
    }
    outFile<<">"<<endl;
    for(auto &it:svgRoot->children){
      print(it,outFile);
    }
    outFile<<"</"<<svgRoot->name<<">"<<endl;;

  }
};

int main(int argc,char **argv){
string line;
vector<CVS*> csv_vec;
// vector<string> item;
// vector<vector<string> > csvItem;
// vector<vector<vector<string> > >totalCsvItem;
SVG* root_svg = new SVG("html");
Selection* selection = new Selection(root_svg);


//file stream to vector.
int j=0;
  for(int i=1; i<argc;i++){
  CVS *csv = new CVS();
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

        csv->field.push_back(item);
        isfirst++;
      }else if(isfirst==2){
        isfirst++;
        csv->type.push_back(item);
      }else{
        csv->data.push_back(item);        
      }
    }
    csv_vec.push_back(csv);
  }

  // cout<<"---------------csv io check----------------"<<endl;

  // for(auto &csvObj:csv_vec){
  //   for(auto &it:*csvObj->field[0]){
  //     cout<<it<<"  ";
  //   }
  //   cout<<endl;
  //   for(auto &it:*csvObj->type[0]){
  //     cout<<it<<"  ";
  //   }
  //   cout<<endl;
  
  //   for(auto &item:csvObj->data){
  //     for(auto &it:*item){
  //         cout<<it<<"  ";
  //     }
  //     cout<<endl;
  //   }
  // }
  // cout<<"---------------csv i/o check end-------------"<<endl;

// selection->append("head");
// cout<<selection->parentSvg.back()->name<<endl;
// selection->select("rect");
// cout<<selection->parentSvg.back()->name<<endl;
// selection->enter(0,csv_vec);
// selection->enter(1,csv_vec);
// cout<<"---------------------select & enter check-----------"<<endl;
// for(auto &it:selection->selectedSvg){
//   for(auto& item:it->data){
//         cout<<item<<"  ";
//   }
//   cout<<endl;
// }
// cout<<"---------------------select & enter check-----------"<<endl;
// selection->update(1,csv_vec);
// cout<<"---------------------select & update check-----------"<<endl;
// for(auto &it:selection->selectedSvg){
//   for(auto& item:it->data){
//         cout<<item<<"  ";
//   }
//   cout<<endl;
// }
// cout<<"---------------------select & update check-----------"<<endl;
  
// // selection->exit(1,csv_vec); 

// // cout<<"---------------------select & exit check-----------"<<endl;
// // for(auto &it:selection->selectedSvg){
// //   for(auto& item:it->data){
// //         cout<<item<<"  ";
// //   }
// //   cout<<endl;
// // }
// // cout<<"---------------------select & exit check-----------"<<endl;

// selection->cattr("width","1000");
// selection->cattr("weight","500");
// selection->tattr("10","20");
// selection->dattr(csv_vec,"name","name");

// selection->end();
// selection->select("rect");
// cout<<"---------------------select & attr check-----------"<<endl;

// for(auto &it:selection->selectedSvg){
//   for(auto& item:it->data){
//         cout<<item<<"  ";
//   }
//   cout<<"cAttr ";
//   for(auto& item2:it->cattr){
//         cout<<item2.first<<" : "<<item2.second<<" ";
//   }
//   cout<<"tAttr ";

//   for(auto& item3:it->tattr){
//         cout<<"x-"<<item3.first<<" : "<<"y-"<<item3.second<<" ";
//   }
//   cout<<endl;
// }
// cout<<"---------------------select & attr check-----------"<<endl;

//   delete(root_svg);
//   delete(selection);

  // cin.ignore(256,'\n');
  string command, subcommand1,subcommand2;
  double d_command1, d_command2;
  int csvIndex;
  vector<double> parameters;
  while(cin>>command){
    cout<<command<<endl;
    if(command=="append"){
      cin>>subcommand1;
      selection->append(subcommand1);
    }
    else if(command=="select"||command=="selectAll"){
      cin>>subcommand1;
      selection->select(subcommand1);
      cout<<selection->selectedSvg.size()<<endl;

    }
    else if(command=="remove"){
      selection->remove();
    }
    else if(command=="end"){
      if(selection->selectedSvg[0]->name=="html"){
        return 0;
      }
      selection->end();
    }
    else if(command=="enter"){
      cin>>csvIndex;
      selection->enter(csvIndex-1,csv_vec);
    }
    else if(command=="update"){
      cin>>csvIndex;
      selection->update(csvIndex-1,csv_vec);
    }
    else if(command=="exit"){
      cin>>csvIndex;
      selection->exit(csvIndex-1,csv_vec);
    }
    else if(command=="cattr"){
      cin>>subcommand1>>subcommand2;
      selection->cattr(subcommand1,subcommand2);
    }
    else if(command=="tattr"){
      cin>>d_command1>>d_command2;
      selection->tattr(d_command1,d_command2);
    }
    else if(command=="dattr"){
      string line;
      getline(cin,line);
      // cout<<command<<endl;
      istringstream ss(line);
      ss>>subcommand1>>subcommand2;
      while(ss>>d_command1){
        // cout<<d_command1<<endl;
        parameters.push_back(d_command1);
      }
      if(parameters.size()==0){
        selection->dattr(csv_vec,subcommand1,subcommand2);
      }
      else if(parameters.size()==1){
        selection->dattr(csv_vec,subcommand1,subcommand2,parameters[0]);
      }
      else{
        selection->dattr(csv_vec,subcommand1,subcommand2,parameters[0],parameters[1]);
      }
      parameters.clear();
    }
    else if(command=="print"){
      cin>>subcommand1;
      ofstream outFile(subcommand1);
      selection->print(root_svg,outFile);
      outFile.close();
    }
cout<<"---------------------select & attr check-----------"<<endl;

for(auto &it:selection->selectedSvg){
  for(auto& item:it->data){
        cout<<item<<"  ";
  }
  // cout<<"cAttr ";
  for(auto& item2:it->cattr){
        cout<<item2.first<<" : "<<item2.second<<" ";
  }
  // cout<<"tAttr ";

  for(auto& item3:it->tattr){
        cout<<"x-"<<item3.first<<" : "<<"y-"<<item3.second<<" ";
  }
  cout<<endl;
}
cout<<"---------------------select & attr check-----------"<<endl;

  }
  delete(root_svg);
  for(auto &it:csv_vec){
    delete(it);
  }
  return 0;
}
