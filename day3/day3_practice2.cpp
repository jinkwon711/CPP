#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main(void){
  string ifile = "text.txt";
  string line, word , combined;

  //ifstream, ofstream
  ifstream ifs(ifile);
  ofstream ofs(ifile+".copy");
  if(ifs && ofs){
    string line;
    while(getline(ifs,line)){
      ofs << line << endl;

    }
  }
  ifs.close();
  ofs.close();

  //istringstream
  vector<string> wordlist;
  while(getline(cin, line)){
    istringstream iss(line);
    while(iss >> word) {
      wordlist.push_back(word);
    }
  }

  //ostringstream
  ostringstream oss;
  while(getline(cin,line)) {
    oss << line;
  }
  combined = oss.str();

}
