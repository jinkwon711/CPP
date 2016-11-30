#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class CSV{
public:
  vector<vector<string>* > field;
  vector<vector<string>* > type;
  vector<vector<string>* > data;
};
class SVG{
public:
  string name;
  vector<string> data{""};
  vector<pair<string,string> > cattr;
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
  vector<SVG *> selectedSvg;
  vector<SVG *> parentSvg;
  Selection(SVG* queryCurrSVG){
    selectedSvg.push_back(queryCurrSVG);
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


  void select(string queryName,string command){
    parentSvg.push_back(selectedSvg[0]);
    selectedSvg.clear();
    for(auto &it:parentSvg.back()->children){
      if(it->name == queryName )
        selectedSvg.push_back(it);
    }
    lastQueryName = queryName;
    // if(command=="selectAll" && selectedSvg.size()!=0){
    //   end();
    // }

  }

  void remove(){
      for(auto &it:selectedSvg){
        for(int i=0; i!=parentSvg.back()->children.size();i++){
          if(parentSvg.back()->children[i]==it){
            parentSvg.back()->children.erase(parentSvg.back()->children.begin()+i);
            i--;
            break;
          }
        }
      }
      for(auto &it:selectedSvg){
        delete(it);
    }
    end();
  }

  void end(){//main안에서 root가 셀렉된경우 함수 종료시키자.

    selectedSvg.clear();
    selectedSvg.push_back(parentSvg.back());
    parentSvg.pop_back();
  }

  void enter(int csvIdx,vector<CSV*> csv_vec){
    if((*(csv_vec[csvIdx]->type[0]))[0]=="string"){
      sort(csv_vec[csvIdx]->data.begin(),csv_vec[csvIdx]->data.end(),
        [](vector<string>* left,vector<string> *right){return (*left)[0]<(*right)[0];});
    }
    else if((*(csv_vec[csvIdx]->type[0]))[0]=="float"){
      sort(csv_vec[csvIdx]->data.begin(),csv_vec[csvIdx]->data.end(),
        [](vector<string>* left,vector<string> *right){return stof((*left)[0])<stof((*right)[0]);});

    }
    else if((*(csv_vec[csvIdx]->type[0]))[0]=="int"){
      sort(csv_vec[csvIdx]->data.begin(),csv_vec[csvIdx]->data.end(),
        [](vector<string>* left,vector<string> *right){return stoi((*left)[0])<stoi((*right)[0]);});
    }

    int exist;
  vector<vector<string>* >  temp1;
    for(auto &csvItem:csv_vec[csvIdx]->data){
      exist = 0;
      for(int i=0; i!=selectedSvg.size(); i++){
        if((*csvItem)[0]==selectedSvg[i]->data[0]){
          exist =1;
          break;
        }
      }
      if(exist==0){
        temp1.push_back(csvItem);
        
      }
    }
    selectedSvg.clear();
    for(auto &it:temp1){
      append(lastQueryName,it);
    }

  }

  void update(int csvIdx,vector<CSV*> csv_vec){
    if((*(csv_vec[csvIdx]->type[0]))[0]=="string"){
      sort(csv_vec[csvIdx]->data.begin(),csv_vec[csvIdx]->data.end(),
        [](vector<string>* left,vector<string> *right){return (*left)[0]<(*right)[0];});
    }
    else if((*(csv_vec[csvIdx]->type[0]))[0]=="float"){
      sort(csv_vec[csvIdx]->data.begin(),csv_vec[csvIdx]->data.end(),
        [](vector<string>* left,vector<string> *right){return stof((*left)[0])<stof((*right)[0]);});

    }
    else if((*(csv_vec[csvIdx]->type[0]))[0]=="int"){
      sort(csv_vec[csvIdx]->data.begin(),csv_vec[csvIdx]->data.end(),
        [](vector<string>* left,vector<string> *right){return stoi((*left)[0])<stoi((*right)[0]);});

    }
    vector<SVG *> tempSvg;
    tempSvg = selectedSvg;
    int exist;
    for(int i=0; i!=selectedSvg.size();i++){
      exist=0;
      for(auto &csvItem:csv_vec[csvIdx]->data){
        if((*csvItem)[0]==selectedSvg[i]->data[0]){
          selectedSvg[i]->data= (*csvItem);
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
  void exit(int csvIdx,vector<CSV*> csv_vec){
    for(auto &csvItem:csv_vec[csvIdx]->data){
      for(int i=0; i!=selectedSvg.size();i++){
        if((*csvItem)[0]==selectedSvg[i]->data[0]){
          selectedSvg.erase(selectedSvg.begin()+i);
          i--;
          break;
        }
      }
    }
  }

  void cattr(string attrName, string attrValue){
    int exist;
    for(auto &svgItem:selectedSvg){
      exist=0;
      for(auto& attr:svgItem->cattr){
        if(attr.first==attrName){
          attr={attrName,attrValue};
          exist =1;
          break;
        }
      }
      if(!exist){
        svgItem->cattr.push_back({attrName,attrValue});
      }
    }


  }
  void tattr(double x_mul,double y_mul){
    int exist=0;
    int idx=0;
    for(auto &svgItem:selectedSvg){
      if(!svgItem->tattr.size()){
        svgItem->tattr.push_back({x_mul*idx,y_mul*idx});
        idx++;
      }
      else{
        svgItem->tattr[0]={x_mul*idx,y_mul*idx};
        idx++;
      }
    }
  }
  void dattr(vector<CSV*> csv_vec,string attrName,string valueName,double mul=1.0,double add = 0.0){
    int dataIdx;
    int isString=0;
    for(int i=0;csv_vec[0]->field[0]->size();i++){
      if((*(csv_vec[0]->field[0]))[i]==valueName){
        dataIdx =i;
        if((*(csv_vec[0]->type[0]))[i]=="string") isString=1;
        break;
      }
    }
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
vector<CSV*> csv_vec;
SVG* root_svg = new SVG("html");
Selection* selection = new Selection(root_svg);


//file stream to vector.
int j=0;
  for(int i=1; i<argc;i++){
  CSV *csv = new CSV();
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

  string command, subcommand1,subcommand2;
  double d_command1, d_command2;
  int csvIndex;
  vector<double> parameters;
  while(cin>>command){
    if(command=="append"){
      cin>>subcommand1;
      selection->append(subcommand1);
    }
    else if(command=="select"||command=="selectAll"){
      cin>>subcommand1;
      selection->select(subcommand1,command);

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
      istringstream ss(line);
      ss>>subcommand1>>subcommand2;
      while(ss>>d_command1){
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
    string temp;
    if(selection->parentSvg.size()==0){
      temp = "hi";
    }
    else {
      temp = selection->parentSvg.back()->name;
    }
    // cout<<"명령어: " <<command<<subcommand1<<endl;
    // cout<<"부모: "<< temp<<endl;
  }
  delete(root_svg);
  for(auto &it:csv_vec){
    delete(it);
  }
  return 0;
}
