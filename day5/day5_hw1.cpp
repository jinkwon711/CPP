#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main(void){

    vector<string> data;
    string line;
    string info;
    string country1,country2,point1,point2;

    vector<string> infoList;

    while(getline(cin,line)){
        istringstream ss(line);
        while(ss>>info){
            infoList.push_back(info);
        }

        country1=infoList[0];
        country2=infoList[3];
        point1 = infoList[1];
        point2 = infoList[2];
         cout<<country1<<" "<<country2<<" "<< point1<<" "<<point2<<endl;

    }
    cout<<country1<<" "<<country2<<" "<< point1<<" "<<point2<<endl;

    // for(int i=0; i!=4;i++){
    //     while(i)
    // }

    // for(auto &it:infoList){
    //     for(auto &it2:data){
    //         if(it2[0]==it1){

    //         }
    //     }
    //     if()
    // }

        // while(ss>>info){
        //     for(auto &it:data){
        //     }
    //     }
    // }


    return 0;

}
