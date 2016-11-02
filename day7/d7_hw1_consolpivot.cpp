#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

int currPriority1=0;
int currPriority2=0;
int cat=0;
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
    int cnt;
    vector<int> Priority;

    bool operator > (const Movie& m) const
     {
        // return (Priority[0]>=m.Priority[0]);
        if(cat==0) {
            return (Priority[0]>=m.Priority[0]);
        }
        else if(cat==1) {
            return (Priority[1]>=m.Priority[1]);
        }
        return 0;
     }

    Movie()=default;
    Movie(int n):cnt(n){}


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


void print_originaltable(int n){
    cout<<"Name\t"<<"Genre\t"<<"Source\t"<<"Production\t"<<"Gross\t"<<"Rating\t"<<"Priority1\t"<<"Priority2"<<endl;
    for(int i=0; i!=n;i++){
        cout<<movie_list[i].name<<"\t";
        cout<<movie_list[i].genre<<"\t";
        cout<<movie_list[i].source<<"\t";
        cout<<movie_list[i].production<<"\t";
        cout<<movie_list[i].gross<<"\t";
        cout<<movie_list[i].rating<<"\t";
        cout<<movie_list[i].Priority[0]<<"\t";
        cout<<movie_list[i].Priority[1]<<endl;
    }

}
void print_sortedtable(int n){
    cout<<"Name\t"<<"Genre\t"<<"Source\t"<<"Production\t"<<"Gross\t"<<"Rating\t"<<"Priority1\t"<<"Priority2"<<endl;
    for(int i=0; i!=n;i++){
        cout<<pivot_table1[i].name<<"\t";
        cout<<pivot_table1[i].genre<<"\t";
        cout<<pivot_table1[i].source<<"\t";
        cout<<pivot_table1[i].production<<"\t";
        cout<<pivot_table1[i].gross<<"\t";
        cout<<pivot_table1[i].rating<<"\t";
        cout<<pivot_table1[i].Priority[0]<<"\t";
        cout<<pivot_table1[i].Priority[1]<<endl;
    }

}
void print_pivoted_whole(int n, int c_info,int i_info,string func){
    cout<<"Name\t"<<"Genre\t"<<"Source\t"<<"Production\t"<<"Gross\t"<<"Rating\t"<<"Priority1\t"<<"Priority2"<<endl;
    for(int i=0; i!=n;i++){
        cout<<pivot_table2[i].name<<"\t";
        cout<<pivot_table2[i].genre<<"\t";
        cout<<pivot_table2[i].source<<"\t";
        cout<<pivot_table2[i].production<<"\t";
        cout<<pivot_table2[i].gross<<"\t";
        cout<<pivot_table2[i].rating<<"\t";
        cout<<pivot_table2[i].Priority[0]<<"\t";
        cout<<pivot_table2[i].Priority[1]<<endl;
    }

}

void print_pivottable(int n, int c_info,int i_info,string func){

    switch(c_info){
        case 0: cout<<"Genre\t";break;
        case 1: cout<<"Source\t";break;
        case 3:cout<<"Genre\t"<<"Source\t";break;
    }
    switch(i_info){
        case 0: cout<<"Production\t"; break;
        case 1: cout<<"Gross\t"; break;
        case 2: cout<<"Ratring\t"; break;
    }
    cout<<endl;

    for(int i=0; i!=n;i++){
        switch(c_info){
        case 0: cout<<pivot_table2[i].Sval[0]<<"\t"; break;
        case 1: cout<<pivot_table2[i].Sval[1]<<"\t"; break;
        case 3:
            cout<<pivot_table2[i].Sval[0]<<"\t"<<pivot_table2[i].Sval[1]<<"\t";break;
        }

        if(func!="cnt"){
            switch(i_info){
            case 0: cout<<pivot_table2[i].production<<"\t"; break;
            case 1: cout<<pivot_table2[i].gross<<"\t"; break;
            case 2: cout<<pivot_table2[i].rating<<"\t"; break;
            }
            cout<<endl;
        }
        else{
            cout<<pivot_table2[i].cnt<<"\t";
            cout<<endl;
        }
    }
}



 void make_pivot1(int cat_index, int info_index,string func,string command){
    int inputPriority=0;
    pivot_table1.clear();
    pivot_table1 = movie_list;
    pivot_table2.clear();
    cat=cat_index;
    if(command=="pivot2"){
        cout<<command<<endl;
        if(cat_index==1) cat_index--;
        else cat_index++;
    }
    stable_sort(pivot_table1.begin(),pivot_table1.end(),greater<Movie>());

    reverse(pivot_table1.begin(),pivot_table1.end());
    if(func=="max"){
        pivot_table2.push_back(pivot_table1[0]);
        for(int i=1; i!=pivot_table1.size();i++){
            if(pivot_table2.back().Priority[cat_index]==pivot_table1[i].Priority[cat_index]&&pivot_table2.back().Priority[cat]==pivot_table1[i].Priority[cat]){

                if(pivot_table2.back().Dval[info_index]<pivot_table1[i].Dval[info_index]){
                    pivot_table2.pop_back();
                    pivot_table2.push_back(pivot_table1[i]);
                }
            }
            else{
                pivot_table2.push_back(pivot_table1[i]);
            }
        }
    }
    else if(func=="min"){
        pivot_table2.push_back(pivot_table1[0]);
        for(int i=1; i!=pivot_table1.size();i++){
            if(pivot_table2.back().Priority[cat_index]==pivot_table1[i].Priority[cat_index]&&pivot_table2.back().Priority[cat]==pivot_table1[i].Priority[cat]){

                if(pivot_table2.back().Dval[info_index]>pivot_table1[i].Dval[info_index]){
                    pivot_table2.pop_back();
                    pivot_table2.push_back(pivot_table1[i]);
                }
            }
            else{
                pivot_table2.push_back(pivot_table1[i]);
            }
        }
    }
    else if(func=="ave"){
        int cnt;
        pivot_table2.push_back(pivot_table1[0]);
        for(int i=1; i!=pivot_table1.size();i++){
            if(pivot_table2.back().Priority[cat_index]==pivot_table1[i].Priority[cat_index]&&pivot_table2.back().Priority[cat]==pivot_table1[i].Priority[cat]){
                pivot_table2.back().Dval[info_index]+=pivot_table1[i].Dval[info_index];
                cnt++;
            }
            else{
                pivot_table2.back().Dval[info_index]/=cnt+1;
                pivot_table2.push_back(pivot_table1[i]);
                cnt=0;
            }
        }
        pivot_table2.back().Dval[info_index]/=cnt+1;
        cnt=0;

    }
    else if(func=="tot"){

    }
    else if(func=="cnt"){
        int cnt;
        pivot_table2.push_back(pivot_table1[0]);
        for(int i=1; i!=pivot_table1.size();i++){
            if(pivot_table2.back().Priority[cat_index]==pivot_table1[i].Priority[cat_index]&&pivot_table2.back().Priority[cat]==pivot_table1[i].Priority[cat]){
                cnt++;
            }
            else{
                pivot_table2.back().cnt=cnt+1;
                pivot_table2.push_back(pivot_table1[i]);
                cnt=0;
            }
        }
        pivot_table2.back().cnt=cnt+1;
        cnt=0;
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
    string category2;//didn't use it;;
    string info;
    string op;
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
            cout<<i<<endl;
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
            print_originaltable(numOfMovie);

            cout<<"\n\n"<<endl;
        }
        else if(command=="pivot1"){
            cin>>category;
            cin>>info;
            cin>>op;
            int c_info;
            int i_info;
            vector<string> cat_list;
            if(category=="Genre") c_info=0;
            else c_info=1;

            if(info=="Production") i_info=0;
            else if(info=="Gross") i_info=1;
            else i_info=2;
            make_pivot1(c_info,i_info,op,command);

            // print_sortedtable(pivot_table1.size());
            // print_pivoted_whole(pivot_table2.size(),c_info,i_info,op);

            print_pivottable(pivot_table2.size(),c_info,i_info,op);
        }
        else if(command=="pivot2"){
            cin>>category;
            cin>>category2;
            cin>>info;
            cin>>op;
            int c_info;
            int i_info;
            vector<string> cat_list;
            if(category=="Genre") c_info=0;
            else c_info=1;

            if(info=="Production") i_info=0;
            else if(info=="Gross") i_info=1;
            else i_info=2;
            make_pivot1(c_info,i_info,op,command);

            print_sortedtable(pivot_table1.size());
            print_pivoted_whole(pivot_table2.size(),c_info,i_info,op);
            c_info=3;
            print_pivottable(pivot_table2.size(),c_info,i_info,op);
        }
    }


    return 0;
}