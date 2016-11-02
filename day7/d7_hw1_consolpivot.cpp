#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

class Movie{
public:
    string name;
    string genre;
    string source;
    double production;
    double gross;
    double rating;

    // Movie()=defualt;





};
vector<Movie> movie_list;
vector<Movie> pivot_table1;
vector<Movie> pivot_table2;
vector<string> command_vec;

// istream &operator >> (istream &is, Movie &m) {
//     string temp;
//     cin>>temp
//     //cin.ignore(256, '\n');
//     m.code


// }
void print_originaltable(int n){
    cout<<"Name\t"<<"Genre\t"<<"Source\t"<<"Production\t"<<"Gross\t"<<"Rating\t"<<endl;
    for(int i=0; i!=n;i++){
        cout<<movie_list[i].name<<"\t";
        cout<<movie_list[i].genre<<"\t";
        cout<<movie_list[i].source<<"\t";
        cout<<movie_list[i].production<<"\t";
        cout<<movie_list[i].gross<<"\t";
        cout<<movie_list[i].rating<<endl;
    }

}


int main(){

    int numOfMovie;
    string temp;
    string commandline;
    string command;
    string category;
    string numericInfo;
    string functionName;
    cin>>numOfMovie;//number of movies

    for(int i=0; i<numOfMovie; i++){//iterating over movies
        Movie m;
        cin>>m.name;
        cin>>m.genre;
        cin>>m.source;
        cin>>m.production;
        cin>>m.gross;
        cin>>m.rating;

        movie_list.push_back(m);
    }
    while(cin>>command){
        if(command=="originaltable"){
            print_originaltable(numOfMovie);
        }
        else if(command=="pivot1"){
            cin>>category;
            cin>>numericInfo;
            cin>>functionName;


        }
    }




    return 0;
}