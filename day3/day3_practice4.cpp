#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Bingo{


private:
    string word;
    int startrow;
    int startcol;
    int dataArr[31][31];
    vector<vector<int> > startPoint;
    vector<vector<int> > resultPoint;
    int row, col;

public:
    //constructor
    Bingo(string s, int M, int N, int& arr): word(s),dataArr(&arr){}

    // method

    // bool setArr(int M, int N){
    //     static arr[M][N];
    // }
    void setRow(int i){
        row = i;
    }
    void setCol(int i){
        col = i;
    }
    int getRow(){
        return row;
    }
    int getCol(){
        return col;
    }

    void up(string word, int row, int col, int i =0){
        while(row>=1){
            if(i==word.length()){
                vector<int> temp;
                temp.push_back(row+i);
                temp.push_back(col);
                break;
            }
            if(row!=1){
                up(word,row-1,col, ++i);
            }
        }
    }
    // void down(string word, int row, int col, int i =0){
    //     while(row<=M){
    //         if(i==word.length()){
    //             vector<int> temp;
    //             temp.push_back(row+i);
    //             temp.push_back(col);
    //             break;
    //         }
    //         if(row!=M){
    //             down(word,row+1,col, ++i);
    //         }
    // }
    // void left(string word, int row, int col, int i =0){
    //     while(col>=1){
    //         if(i==word.length()){
    //             vector<int> temp;
    //             temp.push_back(row+i);
    //             temp.push_back(col);
    //             break;
    //         }
    //         if(col!=M){
    //             left(word,row,col-1, ++i)
    //         }
    // }
    // void right(string word, int row, int col, int i =0){
    //     while(col<=N){
    //         if(i==word.length()){
    //             vector<int> temp;
    //             temp.push_back(row+i);
    //             temp.push_back(col);
    //             break;
    //         }
    //         if(col!=N){
    //             right(word,row,col+1, ++i)
    //         }
    // }
    // void upLeft(string word, int row, int col, int i =0){
    //     if(word[i]==)
    //     upleft(word,row-1,col-1, ++i)
    // }
    // bool upRight(string word, int row, int col, int i =0){
    //     if(word[i]==)
    //     up(word,row-1,col+1, ++i)
    // }
    // bool downLeft(string word, int row, int col, int i =0){
    //     if(word[i]==)
    //     up(word,row+1,col-1, ++i)
    // }
    // bool downRight(string word, int row, int col, int i =0){
    //     if(word[i]==)
    //     up(word,row+1,col+1, ++i)
    // }

    void setStartPoint(){
        for(int i =0; i!=M; i++){
            for(int j=0; j!=N; j++){
                if(dataArr[i][j]==word[0]){
                    vector<int> temp;
                    temp.push_back(i+1);
                    temp.push_back(j+1);
                    startPoint.push_back(temp);
                }
            }
        }
    }

    void search(string word, int M, int N){
        setStartPoint();
        for(auto &it: startPoint){
            int row = it[0];
            int col = it[1];

            up(word,M,N);
        }
        int x = resultPoint.back()[0];
        int y = resultPoint.back()[1];

        while(!resultPoint.empty()){
            if(x>resultPoint.back()[0]){
                x = resultPoint.back()[0];
                y = resultPoint.back()[1];
                resultPoint.pop_back();
            }
            else if(x == resultPoint.back()[0]){
                if(y>resultPoint.back()[1]){
                    x = resultPoint.back()[0];
                    y = resultPoint.back()[1];
                    resultPoint.pop_back();
                }
            }
        }
        vector<int> temp;
        temp.push_back(x);
        temp.push_back(y);
        resultPoint.push_back(temp);
    }
};




int main() {
	int T,M,N;

	cin>>T>>M>>N;
    vector<string> wordList;
    char arr[31][31]={'0',};
    string data;
    while(cin>>data){
        static int i=0;
        i++;
        arr[i]=data;
    }
    while(cin>>word){
        wordList.push_back(word);
    }

    for(auto &it :wordList){
        Bingo bg(it,M,N,&arr);

        bg.serach();

        cout<<bg.resultPoint[0][0]<<" "<<bg.resultPoint[0][1]<<endl;
    }





	return 0;
}
