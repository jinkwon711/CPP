#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;


int main(int argc,char **argv){
string line;
vector<string> item;
vector<vector<string> > csvItem;
vector<vector<vector<string> > >totalCsvItem;

  for(int i=0; i<argc;i++){
    ifstream inFile(argv[i]);

    while(!inFile.eof()){
      getline(inFile,line);
      string tempString="";
      for(int i=0; i!=line.length(); i++){
        if(line[i]!=',') tempString+=line[i];
        else{
          item.push_back(tempString);
          tempString="";
        }
        item.push_back(tempString);
      }
      csvItem.push_back(item);

    }
  }
  return 0;
}
