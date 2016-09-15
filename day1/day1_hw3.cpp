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
using namespace std;


int main()
{

string command = "";
string genre= "";
string movie= "";
int i = 0;
string *ptr_command = &command ;
string *ptr_genre = &genre ;
string *ptr_movie = &movie;
int *ptr_i = &i;


    vector<vector<string> > database;
    string input;

    while(getline(cin,input)){
        // cin>> command >> genre >> movie;
        int cnt =0;
        for(auto it :input){
            if (isspace(it)==true){
                cnt++;
            }
            else{
                if(cnt==0){
                    command+= it;
                }
                else if(cnt==1){
                    genre += it;
                }
                else{
                    movie += it;
                }
            }
        }

        if(command =="exit")
            break;

        if(command == "add_genre"){

            database.push_back(vector<string>());
            database[i].push_back(genre);
            *ptr_i = *ptr_i+1;

        }

        if(command == "add_movie"){
            for(auto &it : database){
                if(it[0]==genre){
                    it.push_back(movie);
                }
            }
        }

        if(command =="print_genre"){
            for(auto &it : database){
                if(it[0]==genre){
                    for(auto list :it){
                        if (list==genre){
                            cout<<"--"<<list<<"--"<<endl;
                        }
                        else{
                            cout<<list<<endl;
                        }
                    }
                }
            }
        }

        if(command == "print_all"){
            for(auto &it : database){
                for(unsigned int j=0; j!= it.size();j++){
                    if (j==0){
                        cout<<"--"<<it[j]<<"--"<<endl;
                    }
                    else{
                        if(it[j] != ""){
                            cout<<it[j]<<endl;
                        }
                    }
                }
            }
        }

        if(command == "remove_genre"){
            for(auto &it : database){
                if(it[0]==genre){
                    it.clear();
                    break;
                }
            }
        }

        if(command == "remove_movie"){
            for(auto &it : database){
                if(it[0]==genre){
                    for(auto &list: it){
                        if(list == movie){
                            list.clear();
                            // vector<string>().swap(it);
                            list.shrink_to_fit();
                            break;
                        }
                    }
                }
            }
        }


    *ptr_command = "";
    *ptr_genre= "";
    *ptr_movie= "";
    }


    return 0;
}
