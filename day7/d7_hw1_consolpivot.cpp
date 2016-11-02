#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

int currPriority1=0;
int currPriority2=0;
int cat;
class Movie{
public:
    vector<string> Sval;
    string name;
    string genre;
    string source;
    vector<double> Dval;
    double production;
    double gross;
    double rating;
    vector<int> Priority;

    bool operator > (const Movie& m) const
     {
        if(cat==0) return (Priority[0] > m.Priority[0]);
        else return (Priority[1]>m.Priority[1]);
     }

    // Movie()=defualt;


};
vector<Movie> movie_list;
vector<Movie> temp_list;
vector<string> cat_list;
vector<Movie> pivot_table1;
vector<Movie> pivot_table2;
vector<string> command_vec;
vector<string> genre_list;
vector<string> source_list;
vector<int> cnt_list;

// istream &operator >> (istream &is, Movie &m) {
//     string temp;
//     cin>>temp
//     //cin.ignore(256, '\n');
//     m.code


// }
void print_originaltable(int n){
    cout<<"Name\t"<<"Genre\t"<<"Source\t"<<"Production\t"<<"Gross\t"<<"Rating\t"<<"Priority\t"<<endl;
    for(int i=0; i!=n;i++){
        cout<<movie_list[i].name<<"\t";
        cout<<movie_list[i].genre<<"\t";
        cout<<movie_list[i].source<<"\t";
        cout<<movie_list[i].production<<"\t";
        cout<<movie_list[i].gross<<"\t";
        cout<<movie_list[i].rating<<"\t";
        cout<<movie_list[i].Priority[0]<<endl;
    }

}

void print_pivottable(int n){
    cout<<"Name\t"<<"Genre\t"<<"Source\t"<<"Production\t"<<"Gross\t"<<"Rating\t"<<"Priority\t"<<endl;
    for(int i=0; i!=n;i++){
        cout<<pivot_table1[i].Sval[0]<<"\t";
        cout<<pivot_table1[i].Sval[1]<<"\t";
        cout<<pivot_table1[i].source<<"\t";
        cout<<pivot_table1[i].production<<"\t";
        cout<<pivot_table1[i].gross<<"\t";
        cout<<pivot_table1[i].rating<<"\t";
        cout<<pivot_table1[i].Priority[0]<<endl;
    }

}

// void make_genre_pivot(string info, string func){
//         pivot_table1.clear();
//     int inputPriority=0;
//     while(inputPriority<currPriority){
//         for(int i=0;i!=movie_list.size();i++){
//             if(movie_list[i].priority==inputPriority){
//                 pivot_table1.push_back(movie_list[i]);
//             }
//         }
//         inputPriority++;
//     }

//     if(info=="Production"){

//     }
//  }


 void make_pivot1(int cat_index, int info_index,string func){
    int inputPriority=0;
    pivot_table1 = movie_list;
    stable_sort(pivot_table1.begin(),pivot_table1.end(),greater<Movie>());
    reverse(pivot_table1.begin(),pivot_table1.end());
    if(func=="max"){
        pivot_table2.push_back(pivot_table1[0])
        for(int i=1; i!=pivot_table1.size();i++){
            if(pivot_table1.Priority[cat_index]==pivot_table2[cat_index]){
                if(pivot_table2.Sval[0]>pivot_table1.Sval[cat_index])

        }

    }
    else if(func=="min"){

    }
    else if(func=="ave"){

    }
    else if(func=="tot"){

    }
    else if(func=="cnt"){

    }
}






 //    }
 //    pivot_table1.clear();

 //    int inputPriority2=0;

 // }

 // void min(string info,int prior){
 //    int inputPriority=0;
 //    if(prior==1){
 //        for(auto &it:pivot_table1){
 //            pivot_table1[0].priority==inputPriority;
 //        }
 //        for(int i=0; i!=pivot_table1.size();i++){
 //            pivot_table1[i]
 //        }
 //    }
 // }



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
        auto it =find(genre_list.begin(),genre_list.end(),m.genre);
        if(it==genre_list.end()){

            genre_list.push_back(m.genre);

            m.Priority.push_back(currPriority1++);
        }else{

            for(auto &it:movie_list){
                if(it.genre==m.genre){
                    m.Priority.push_back(it.Priority[0]);
                    break;
                }
            }
        }

        //source
        cin>>m.source;
        auto it2 =find(source_list.begin(),source_list.end(),m.source);
        if(it2==source_list.end()){
            source_list.push_back(m.source);


            m.Priority.push_back(currPriority2++);
        }else{
            for(auto &it:movie_list){
                if(it.source==m.source){
                    m.Priority.push_back(it.Priority[1]);
                    break;
                }
            }
        }

        m.Sval.push_back(m.name);
        m.Sval.push_back(m.genre);
        m.Sval.push_back(m.source);
        cin>>m.production;
        cin>>m.gross;
        cin>>m.rating;
        m.Dval.push_back(m.production);
        m.Dval.push_back(m.gross);
        m.Dval.push_back(m.rating);

        movie_list.push_back(m);
    }

    while(cin>>command){
        if(command=="originaltable"){
            // print_originaltable(numOfMovie);;
            cat=1;
            make_pivot1(1,2,"hi");
            print_pivottable(7);
        }
        else if(command=="pivot1"){
            cin>>category;
            cin>>numericInfo;
            cin>>functionName;
            int g_info;
            int i_info;
            int f_info;
            vector<string> cat_list;
            if(category=="Genre") g_info=1;
            else g_info=2;

            if(numericInfo=="Production") i_info=0;
            else if(numericInfo=="Gross") i_info=1;
            else i_info=2;

            if(functionName=="tot"||functionName=="ave"){
                // make_pivot1(g_info,i_info);
            }else{
            //else if(functionName="max"||functionName="min"){
                // make_pivot2(g_info,i_info);
            }


        }
    }


    return 0;
}