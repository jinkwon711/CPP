#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct DragonRank {
  string name;
  char rank;
};

class RankMap{

private:
  vector<DragonRank> rMap;
public:
  RankMap() = default;
  char& operator[](const string &name);
};

char &RankMap::operator[](const string &name){
  for(auto &e :rMap){
    if(e.name ==name) return e.rank;
  }
  DragonRank t{name, ' '};
  rMap.push_back(t);
  return rMap.back().rank;
};

int main(){
  RankMap ranks;
  ranks["DeathWing"];
  ranks["Ysera"] = 'A';
  cout<<"DeathWing's rank : "<<ranks["DeathWing"]<<endl;
  cout<<"oops!"<<endl;
  ranks["DeathWing"]='B';
  cout<<"DeathWing's rank : "<<ranks["DeathWing"]<<endl;
  cout<<"Ysera's rank : "<<ranks["Ysera"]<<endl;
  return 0;
}
