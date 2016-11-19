#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;

class Selection{
public:
  // vector<SVG *> allSvg;
  vector<SVG *> selectedSvg;
  vector<SVG *> currSVG;
  Selection(string queryCurrSVG){
    currSVG.push_back(queryCurrSVG);
  }

  void append(){


  }


  void select(string queryName){
    selectedSvg.clear();
    for(auto &it:currSVG.back()){
      if(it->name = queryName )
        selectedSvg.push_back(it);
    }
  }

  void remove(this){
    selectedSvg.clear();
    selectedSvg.push_back(currSVG.pop_back();
  }



  void svgNotExist(){



  }


}:
class SVG{
public:
  string name;
  vector<pair<string,string> > cAttr;
  // vector<pair<string,string> > dAttr; 
  vector<pair<string,string> > tAttr;

  vector<string> originalData;
  vector<string> changedData;
  vector<SVG *> children;

  SVG(string queryName):name(queryName){};

};



int main(int argc,char **argv){
string line;
vector<string> item;
vector<vector<string> > csvItem;
vector<vector<vector<string> > >totalCsvItem;
SVG root_svg = new SVG("html");
Selection root_selection = new Selection();


//file stream to vector.
  for(int i=1; i<argc;i++){
    ifstream inFile(argv[i]);

    while(!inFile.eof()){
      getline(inFile,line);//getline
      string tempString="";
      for(int i=0; i!=line.length(); i++){
        if(line[i]==','||line[i]=='\0'){
          item.push_back(tempString);
          tempString="";
        }
        else tempString+=line[i];//split by ','
      }
      item.push_back(tempString);
      csvItem.push_back(item);
      item.clear();
      // temp = &csvItem;
    }
    totalCsvItem.push_back(csvItem);
    csvItem.clear();
  }
  //below , used for the input checking
  // for(int i=0; i!=totalCsvItem.size();i++){
  //   for(auto it:totalCsvItem[i]){
  //     for(auto it2:it){
  //       cout<<it2;
  //     }
  //     cout<<endl;
  //   }
  // }






  delete(root_svg);
  delete(root_selection);
  return 0;
}
