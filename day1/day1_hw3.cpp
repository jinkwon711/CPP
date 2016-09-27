//============================================================================
// Name        : day2_realhw.cpp
// Author      : jin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


int main()
{

string command = "";
string genre= "";
string movie= "";

string *ptr_command = &command ;
string *ptr_genre = &genre ;
string *ptr_movie = &movie;


    vector<vector<string> > database;
    string input;

    while(true){
        cin>> command >> genre >> movie;
        getline(cin,input);

        stringstream a;

        a.str(input);

        a >> command;
        a >> genre;
        a >> movie;

        genre = "--"+genre+"--";


        if(command =="exit")
            break;

        if(command == "add_genre"){
            database.push_back(vector<string> (1,genre));

        }

        if(command == "add_movie"){
            for(auto &it : database){
                if(it.empty() == false){
                    if(it[0]==genre){
                        it.push_back(movie);
                    }
                }
            }
        }

        if(command =="print_genre"){
            for(auto &it : database){
                if(it[0]==genre){
                    for(auto list :it){
                        cout<<list<<endl;
                    }
                }
            }
        }

        if(command == "print_all"){
            for(auto &it : database){
                for(unsigned int j=0; j!= it.size();j++){
                    if(it[j] != ""){
                        cout<<it[j]<<endl;
                    }
                }
            }
        }

        if(command == "remove_genre"){
            for(auto &it : database){
                if(it[0]==genre){
                    it.clear();
                    // database.shrink_to_fit();
                }
            }
        }

        if(command == "remove_movie"){
            for(auto &it : database){
                if(it[0]==genre){
                    for(unsigned int j = 0 ; j != it.size();j++){
                        if(it[j] == movie){
                            it.erase(it.begin()+j);
                            j--;
                        }
                    }
                }
            }
        }

    // *ptr_command = "";
    // *ptr_genre= "";
    // *ptr_movie= "";
    }

    return 0;
}
