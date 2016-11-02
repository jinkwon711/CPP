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
            return (Priority[0]==m.Priority[0]?Priority[1]>=m.Priority[1]:Priority[0]>m.Priority[0]);
        }
        else if(cat==1) {
            return (Priority[1]==m.Priority[1]?Priority[0]>=m.Priority[0]:Priority[1]>m.Priority[1]);
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
    cout<<"Name\t"<<"Genre\t"<<"Source\t"<<"Production\t"<<"Gross\t"<<"Rating"<<endl;
    for(int i=0; i!=n;i++){
        cout<<movie_list[i].name<<"\t";
        cout<<movie_list[i].genre<<"\t";
        cout<<movie_list[i].source<<"\t";
        cout<<movie_list[i].production<<"\t";
        cout<<movie_list[i].gross<<"\t";
        cout<<movie_list[i].rating<<endl;
        // cout<<movie_list[i].Priority[0]<<"\t";
        // cout<<movie_list[i].Priority[1]<<endl;
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
        cout<<pivot_table2[i].Sval[0]<<"\t";
        cout<<pivot_table2[i].Sval[1]<<"\t";
        cout<<pivot_table2[i].Dval[0]<<"\t";
        cout<<pivot_table2[i].Dval[1]<<"\t";
        cout<<pivot_table2[i].Dval[2]<<"\t";
        cout<<pivot_table2[i].Priority[0]<<"\t";
        cout<<pivot_table2[i].Priority[1]<<endl;
    }

}

void print_pivottable(int n, int c_info,int i_info,string func){
        cout.precision(2);
        cout<<fixed;

    switch(c_info){
        case 0: cout<<"Genre\t";break;
        case 1: cout<<"Source\t";break;
        case 3:
            if(cat==0)cout<<"Genre\t"<<"Source\t";
            else cout<<"Source\t"<<"Genre\t";
            break;
    }
    switch(i_info){
        case 0: cout<<"Production"; break;
        case 1: cout<<"Gross"; break;
        case 2: cout<<"Rating"; break;
    }
    cout<<endl;

    for(int i=0; i!=n;i++){
        switch(c_info){
        case 0: cout<<pivot_table2[i].Sval[0]<<"\t"; break;
        case 1: cout<<pivot_table2[i].Sval[1]<<"\t"; break;
        case 3:
            if(cat==0){
            cout<<pivot_table2[i].Sval[0]<<"\t"<<pivot_table2[i].Sval[1]<<"\t";break;
            }
            else{
                cout<<pivot_table2[i].Sval[1]<<"\t"<<pivot_table2[i].Sval[0]<<"\t";
                break;
            }
        }

        if(func!="cnt"){
            switch(i_info){
            case 0: cout<<pivot_table2[i].Dval[0]; break;
            case 1: cout<<pivot_table2[i].Dval[1]; break;
            case 2: cout<<pivot_table2[i].Dval[2]; break;
            }
            cout<<endl;
        }
        else{
            cout<<pivot_table2[i].cnt;
            cout<<endl;
        }
    }
}

void print_pivotchart1(int n, int c_index,int i_index,string func){
    cout.precision(2);
        cout<<fixed;

    //find max,min
    double max;
    double min;
    max = pivot_table2[0].Dval[i_index];
    min = pivot_table2[0].Dval[i_index];
    for(int i=1; i!=n;i++){
        max=max>pivot_table2[i].Dval[i_index]?max:pivot_table2[i].Dval[i_index];
        min=min<pivot_table2[i].Dval[i_index]?min:pivot_table2[i].Dval[i_index];
    }

    for(int i=0; i!=n;i++){
        int code;
        int length;
        code=65+i;
        int j=1;
        while(j){
            if(pivot_table2[i].Dval[i_index]==min){
                length=0;
                break;
            }
            else if(pivot_table2[i].Dval[i_index]==max){length=20;
                break;
            }
            else{
                if(((min+j*(max-min)/20)>=pivot_table2[i].Dval[i_index])&&(pivot_table2[i].Dval[i_index]>min+(j-1)*(max-min)/20)){
                    length=j;
                    break;
                }
                j++;
            }
        }

        cout<<(char)code<<"|";
        for(int i=0; i!=length;i++){
            cout<<"=";
        }

        if(func!="cnt"){
            switch(i_index){
            case 0: cout<<pivot_table2[i].Dval[0]<<"\t"; break;
            case 1: cout<<pivot_table2[i].Dval[1]<<"\t"; break;
            case 2: cout<<pivot_table2[i].Dval[2]<<"\t"; break;
            }
            cout<<endl;
        }
        else{
            cout<<pivot_table2[i].cnt<<"\t";
            cout<<endl;
        }
    }
    for(int i=0; i!=25;i++){
        cout<<'-';
    }
    cout<<endl;
    for(int i=0; i!=n; i++){
        int code = 65+i;
            cout<<(char)code<<":"<<" ";
            cout<<pivot_table2[i].Sval[0];
        cout<<endl;
    }
}




void print_pivotchart2(int n, int c_index,int i_index,string func){
    cout.precision(2);
        cout<<fixed;

    //find max,min
    double max;
    double min;
    max = pivot_table2[0].Dval[i_index];
    min = pivot_table2[0].Dval[i_index];
    for(int i=1; i!=n;i++){
        max=max>pivot_table2[i].Dval[i_index]?max:pivot_table2[i].Dval[i_index];
        min=min<pivot_table2[i].Dval[i_index]?min:pivot_table2[i].Dval[i_index];
    }

    for(int i=0; i!=n;i++){
        int code;
        int length;
        code=65;
        int j=1;
        while(j){
            if(pivot_table2[i].Dval[i_index]==min){
                length=0;
                break;
            }
            else if(pivot_table2[i].Dval[i_index]==max){length=20;
                break;
            }
            else{
                if(((min+j*(max-min)/20)>=pivot_table2[i].Dval[i_index])&&(pivot_table2[i].Dval[i_index]>min+(j-1)*(max-min)/20)){
                    length=j;
                    break;
                }
                j++;
            }
        }
        if(cat==0){
            cout<<(char)(code+pivot_table2[i].Priority[0])<<(1+pivot_table2[i].Priority[1])<<"|";
            for(int i=0; i!=length;i++){
            cout<<"=";
            }
            if(func!="cnt"){
                switch(i_index){
                case 0: cout<<pivot_table2[i].Dval[0]<<"\t"; break;
                case 1: cout<<pivot_table2[i].Dval[1]<<"\t"; break;
                case 2: cout<<pivot_table2[i].Dval[2]<<"\t"; break;
                }
                cout<<endl;
            }
            else{
                cout<<pivot_table2[i].cnt<<"\t";
                cout<<endl;
            }
            if(i<n-1){
                    if(pivot_table2[i].Priority[1]<currPriority1){
                        if(pivot_table2[i+1].Priority[0]==pivot_table2[i].Priority[0]&&pivot_table2[i+1].Priority[1]==pivot_table2[i].Priority[1]+1){
                        }
                        else{
                            cout<<"  "<<"|"<<endl;

                        }
                    }
                }

        }
        else{
            cout<<(1+pivot_table2[i].Priority[1])<<(char)(code+pivot_table2[i].Priority[0])<<"|";
            for(int i=0; i!=length;i++){
                cout<<"=";
                }
                if(func!="cnt"){
                    switch(i_index){
                    case 0: cout<<pivot_table2[i].Dval[0]<<"\t"; break;
                    case 1: cout<<pivot_table2[i].Dval[1]<<"\t"; break;
                    case 2: cout<<pivot_table2[i].Dval[2]<<"\t"; break;
                    }
                    cout<<endl;
                }
                else{
                    cout<<pivot_table2[i].cnt<<"\t";
                    cout<<endl;
                }

                if(i<n-1){
                    if(pivot_table2[i].Priority[0]<currPriority1){
                        if(pivot_table2[i+1].Priority[1]==pivot_table2[i].Priority[1]&&pivot_table2[i+1].Priority[0]==pivot_table2[i].Priority[0]+1){
                        }
                        else{
                            cout<<"  "<<"|"<<endl;

                        }
                    }
                }
        }

     }
    for(int i=0; i!=25;i++){
        cout<<'-';
    }
    cout<<endl;

    for(int i=0; i!=currPriority1){


    }
    for(int i=0; i!=currPriority1){


    }

    for(int i=0; i!=n; i++){
        int code = 65+i;
        if(cat==0){
        cout<<(char)code<<"1"<<":"<<" ";
        cout<<pivot_table2[i].Sval[0]<<"\t"<<pivot_table2[i].Sval[1]<<"\t";break;
        }
        else{
            cout<<pivot_table2[i].Sval[1]<<"\t"<<pivot_table2[i].Sval[0]<<"\t";
            break;
        }

        cout<<endl;
    }
}

 void make_pivot1(int c_index, int i_index,string func,string command){
    int inputPriority=0;
    pivot_table1.clear();
    pivot_table1 = movie_list;
    pivot_table2.clear();
    cat=c_index;
    if(command=="pivot2"){
        if(c_index==1) c_index--;
        else c_index++;
    }
    stable_sort(pivot_table1.begin(),pivot_table1.end(),greater<Movie>());


    reverse(pivot_table1.begin(),pivot_table1.end());
    if(func=="max"){
        pivot_table2.push_back(pivot_table1[0]);
        for(int i=1; i!=pivot_table1.size();i++){
            if(pivot_table2.back().Priority[c_index]==pivot_table1[i].Priority[c_index]&&pivot_table2.back().Priority[cat]==pivot_table1[i].Priority[cat]){

                if(pivot_table2.back().Dval[i_index]<pivot_table1[i].Dval[i_index]){
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
            if(pivot_table2.back().Priority[c_index]==pivot_table1[i].Priority[c_index]&&pivot_table2.back().Priority[cat]==pivot_table1[i].Priority[cat]){

                if(pivot_table2.back().Dval[i_index]>pivot_table1[i].Dval[i_index]){
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
        int cnt=0;
        pivot_table2.push_back(pivot_table1[0]);
        for(int i=1; i!=pivot_table1.size();i++){
            if(pivot_table2.back().Priority[c_index]==pivot_table1[i].Priority[c_index]&&pivot_table2.back().Priority[cat]==pivot_table1[i].Priority[cat]){

                pivot_table2.back().Dval[i_index]+=pivot_table1[i].Dval[i_index];
                cnt++;
            }
            else{
                pivot_table2.back().Dval[i_index]/=cnt+1;
                pivot_table2.push_back(pivot_table1[i]);
                cnt=0;
            }
        }
        pivot_table2.back().Dval[i_index]/=cnt+1;
        cnt=0;

    }
    else if(func=="tot"){
         int cnt=0;
        pivot_table2.push_back(pivot_table1[0]);
        for(int i=1; i!=pivot_table1.size();i++){
            if(pivot_table2.back().Priority[c_index]==pivot_table1[i].Priority[c_index]&&pivot_table2.back().Priority[cat]==pivot_table1[i].Priority[cat]){

                pivot_table2.back().Dval[i_index]+=pivot_table1[i].Dval[i_index];
            }
            else{
                pivot_table2.push_back(pivot_table1[i]);
            }
        }

    }
    else if(func=="cnt"){
        int cnt;
        pivot_table2.push_back(pivot_table1[0]);
        for(int i=1; i!=pivot_table1.size();i++){
            if(pivot_table2.back().Priority[c_index]==pivot_table1[i].Priority[c_index]&&pivot_table2.back().Priority[cat]==pivot_table1[i].Priority[cat]){
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

int main(){

    int numOfMovie;
    string temp;
    string commandline;
    string command;
    string lastCommand;
    string category;
    string category2;//didn't use it;;
    string info;
    string op;
    cin>>numOfMovie;//number of movies
    int c_info;
    int i_info;

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
        }
        else if(command=="pivot1"){
            cin>>category;
            cin>>info;
            cin>>op;
            vector<string> cat_list;
            if(category=="Genre") c_info=0;
            else c_info=1;

            if(info=="Production") i_info=0;
            else if(info=="Gross") i_info=1;
            else i_info=2;
            make_pivot1(c_info,i_info,op,command);
            lastCommand =command;


            // print_sortedtable(pivot_table1.size());
            // print_pivoted_whole(pivot_table2.size(),c_info,i_info,op);

            // print_pivottable(pivot_table2.size(),c_info,i_info,op);
        }
        else if(command=="pivot2"){
            cin>>category;
            cin>>category2;
            cin>>info;
            cin>>op;

            vector<string> cat_list;
            if(category=="Genre") c_info=0;
            else c_info=1;

            if(info=="Production") i_info=0;
            else if(info=="Gross") i_info=1;
            else i_info=2;
            make_pivot1(c_info,i_info,op,command);
                        print_pivoted_whole(pivot_table2.size(),c_info,i_info,op);


            lastCommand =command;
        }else if(command=="pivottable"){
            if(lastCommand=="pivot2"){
                c_info=3;
            }

            print_pivottable(pivot_table2.size(),c_info,i_info,op);

        }else if(command=="pivotchart"){
            if(lastCommand=="pivot2"){
                print_pivotchart2(pivot_table2.size(),c_info,i_info,op);
            }
            else{
                print_pivotchart1(pivot_table2.size(),c_info,i_info,op);
            }

        }else{
            return 0;
        }

    }


    return 0;
}