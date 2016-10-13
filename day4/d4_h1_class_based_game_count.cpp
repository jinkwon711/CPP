#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;


class Game{
private:
    string name;
    int game;
    int win;
    int lose;
    int tie;
    int goalByMe;
    int goalByOther;
    int goalDiff;
    int gamePoint;
    bool rankTie;
public:

    Game(string s):name(s), game(0), win(0), lose(0),
                tie(0), goalByMe(0), goalByOther(0), goalDiff(0), gamePoint(0),rankTie(0){  }



    bool operator > (Game gm) {
            if(gamePoint>gm.gamePoint){
                return true;
            }
            else if(gamePoint!=gm.gamePoint){
                return false;
            }
            else if(win> gm.win){
                return true;
            }
            else if(win!= gm.win){
                return false;
            }
            else if(goalDiff>gm.goalDiff){
                return true;
            }
            else if(goalDiff!=gm.goalDiff){
                return false;
            }
            else if(goalDiff>gm.goalDiff){
                return true;
            }
            else if(goalDiff!=gm.goalDiff){
                return false;
            }
            else if(goalByMe>gm.goalByMe){
                return true;
            }
            else if(goalByMe!=gm.goalByMe){
                return false;
            }
            else if(game<gm.game){
                return true;
            }
            else if(game!=gm.game){
                return false;
            }
            else if(name<gm.name){
                setRankTie();
                gm.setRankTie();
                return true;
            }
            else if(name!=gm.name){
                setRankTie();
                gm.setRankTie();
                return false;
            }
        }

    void setGame(){
        game++;
    }
    void setWin(){
        win++;
    }
    void setLose(){
        lose++;
    }
    void setTie(){
        tie++;
    }
    void setGoalByMe(int a){
        goalByMe += a;
        setGoalDiff(goalByMe-goalByOther);
    }
    void setGoalByOther(int a){
        goalByOther += a;
        setGoalDiff(goalByMe-goalByOther);

    }
    void setGoalDiff(int a){
         goalDiff = a;
    }

    void setGamePoint(){
        gamePoint ++;
    }
    void setRankTie(){
        rankTie=true;
    }

    string getName(){
        return name;
    }
    int getGame(){
        return game;
    }

    int getWin(){
        return win;
    }
    int getLose(){
        return lose;
    }
    int getTie(){
        return tie;
    }
    int getGoalByMe(){
        return goalByMe;
    }
    int getGoalByOther(){
        return goalByOther;
    }
    int getGoalDiff(){
        return goalDiff;
    }
    int getGamePoint(){
        return gamePoint;
    }
    bool getRankTie(){
        return rankTie;
    }






};

void bubbleSort(vector<Game>& v){
    for(int i=0; i!=v.size()-1;i++){
        for(int j=1; j!=v.size(); j++){
            if(!(v[j-1]>v[j])){
                swap(v[j-1],v[j]);
            }
        }
    }
}


int main(void){
    vector<Game> Merge;
    vector<Game> data;
    string line;
    string info;
    string country1,country2;
    int point1,point2;
    vector<string> nameList;
    nameList.push_back("sample");

    vector<string> infoList;

    while(getline(cin,line) && line!="end"){
        istringstream ss(line);

        while(ss>>info){
            infoList.push_back(info);
        }

        country1=infoList[0];
        country2=infoList[3];
        point1 = stoi(infoList[1]);
        point2 = stoi(infoList[2]);
        string status;

        if(point1>point2){
            status = "win";
        }
        else if(point2>point1){
            status = "lose";
        }
        else
        {
            status ="tie";
        }

        if(find(nameList.begin(), nameList.end(), country1) != nameList.end()){
        }
        else{
             data.push_back(Game(country1));
             nameList.push_back(country1);

        }
        if(find(nameList.begin(), nameList.end(), country2) != nameList.end()){
        }
        else{
            data.push_back(Game(country2));
            nameList.push_back(country2);
        }
        for(auto &it:data){
            if(it.getName()==country1){
                it.setGame();
                it.setGoalByMe(point1);
                it.setGoalByOther(point2);
                if(status=="win"){
                    it.setWin();
                    it.setGamePoint();
                    it.setGamePoint();
                    it.setGamePoint();

                }
                else if(status =="lose"){
                    it.setLose();
                }
                else{
                    it.setTie();
                    it.setGamePoint();
                }
            }
            else if(it.getName()==country2){
                it.setGame();
                it.setGoalByMe(point2);
                it.setGoalByOther(point1);
                if(status=="lose"){ // lose is for team1 so it is win;
                    it.setWin();
                    it.setGamePoint();
                    it.setGamePoint();
                    it.setGamePoint();
                }
                else if(status =="win"){
                    it.setLose();
                }
                else{
                    it.setTie();
                    it.setGamePoint();
                }
            }
        }


        infoList.clear();
    }
    if(data.empty()){
        return 0;
    }



    bubbleSort(data);

    for(int i=0, j=1; i!=data.size(); i++){
        cout<<j<<")"<<" "<<data[i].getName()<< " ";
        cout<<data[i].getGame()<<"G"<<" ";
        cout<<data[i].getGamePoint()<<"P"<<" ";
        cout<<data[i].getWin()<<"-"<<data[i].getTie()<<"-"<<data[i].getLose()<<" ";
        cout<<data[i].getGoalByMe()<<"/"<<data[i].getGoalByOther()<<"/"<<data[i].getGoalDiff()<<endl;
        if(i==data.size()-1){
            break;
        }
        if(data[i].getGamePoint()==data[i+1].getGamePoint() 
            && data[i].getWin()==data[i+1].getWin()
            && data[i].getGoalDiff()==data[i+1].getGoalDiff()
            && data[i].getGoalByMe()==data[i+1].getGoalByMe()){
        }else{
            j++;
        }
    }


    return 0;

}
