#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Bingo{


private:
    string word;
    int dataArr[31][31];
    vector<vector<int> > startPoint;
    vector<vector<int> > resultPoint;
    int row, col;
    int M,N;

public:
    //constructor
    Bingo(string s, int M, int N, char arr[31][31]): word(s), M(M), N(N) {
        for(int i=0; i!=31;i++){
            for(int j=0; j!=31; j++){
                dataArr[i][j] = arr[i][j];
            }
        }
    }
    void up(string word, int row, int col, unsigned int i =0){
        while(row>=1 && (dataArr[row-1][col-1]==word[i])){
            if(i+1==word.length()){
               vector<int> temp;
               temp.push_back(row+i);
               temp.push_back(col);
               resultPoint.push_back(temp);
               break;
            }
            i++;
            row--;
        }
    }
    void down(string word, int row, int col, unsigned int i =0){
        while(row<=M && (dataArr[row-1][col-1]==word[i])){
            if(i+1==word.length()){
               vector<int> temp;
               temp.push_back(row-i);
               temp.push_back(col);
               resultPoint.push_back(temp);
                cout<<"hi"<<endl;
               break;
            }
            i++;
            row++;
        }
    }



    //     if(row<=M && (dataArr[row-1][col-1]==word[i])){
    //         if(i+1==word.length()){
    //            vector<int> temp;
    //            temp.push_back(row-i);
    //            temp.push_back(col);
    //            resultPoint.push_back(temp);
    //            return 0;
    //         }
    //         else if(row==M){
    //             return 0;
    //         }
    //         else{
    //             down(word,row+1,col, ++i);
    //         }
    //     }
    //     return 0;
    // }

    int left(string word, int row, int col, unsigned int i =0){
        if(i==word.length()){
           vector<int> temp;
           temp.push_back(row);
           temp.push_back(col+i);
           resultPoint.push_back(temp);
           return 0;
        }

        if(col<1){
            return 0;
        }
        else if(col>=1&&(word[i]==dataArr[row-1][col-1])){
            left(word,row,col-1, ++i);
        }
        return 0;
    }

    int right(string word, int row, int col, unsigned int i =0){
        if(i==word.length()){
           vector<int> temp;
           temp.push_back(row);
           temp.push_back(col-i);
           resultPoint.push_back(temp);
           return 0;
        }

        if(col>N){
            return 0;
        }
        else if(col<=N&&(word[i]==dataArr[row-1][col-1])){
            right(word,row,col+1, ++i);
        }
        return 0;
    }
    int upLeft(string word, int row, int col, unsigned int i =0){
        if(i==word.length()){
            vector<int> temp;
            temp.push_back(row+i);
            temp.push_back(col+i);
            resultPoint.push_back(temp);
            return 0;
        }

        if(row<1 || col<1){
            return 0;
        }
        else if(row>=1 && col>=1&&(word[i]==dataArr[row-1][col-1])){
            upLeft(word,row-1,col-1, ++i);
        }
        return 0;
    }

    int upRight(string word, int row, int col, unsigned int i =0){
        if(i==word.length()){
            vector<int> temp;
            temp.push_back(row+i);
            temp.push_back(col-i);
            resultPoint.push_back(temp);
            return 0;
        }

        if(row<1 || col>N){
            return 0;
        }
        else if(row>=1 && col<=N &&(word[i]==dataArr[row-1][col-1])){
            upRight(word,row-1,col+1, ++i);
        }
        return 0;
    }

    int downLeft(string word, int row, int col, unsigned int i =0){
        if(i==word.length()){
            vector<int> temp;
            temp.push_back(row-i);
            temp.push_back(col+i);
            resultPoint.push_back(temp);
            return 0;
        }

        if(row>M || col<1){
            return 0;
        }
        else if(row<=M && col>=1 &&(word[i]==dataArr[row-1][col-1])){
            downLeft(word,row+1,col-1, ++i);
        }
        return 0;
    }
    int downRight(string word, int row, int col, unsigned int i =0){
        if(i==word.length()){
            vector<int> temp;
            temp.push_back(row-i);
            temp.push_back(col-i);
            resultPoint.push_back(temp);
            return 0;
        }

        if(row>M || col>N){
            return 0;
        }
        else if(row<=M && col<=N &&(word[i]==dataArr[row-1][col-1])){
            downRight(word,row+1,col+1, ++i);
        }
        return 0;
    }

    void setStartPoint(){

        for(int i =0; i!=M; i++){
            for(int j=0; j!=N; j++){
                // cout<<"mid top"<<endl;
                if(dataArr[i][j]==word[0]){
                    vector<int> temp;
                    temp.push_back(i+1);
                    temp.push_back(j+1);
                    startPoint.push_back(temp);
                }
            }
        }
    }

    void search(){
        // cout<<"search top"<<endl;
        setStartPoint();
        // cout<<"search mid"<<endl;
        for(auto &it: startPoint){
            int row = it[0];
            int col = it[1];
            up(word,row,col);
            down(word,row,col);
            left(word,row,col);
            right(word,row,col);
            upLeft(word,row,col);
            upRight(word,row,col);
            downLeft(word,row,col);
            downRight(word,row,col);
        }
        // cout<<"resultPoint"<<endl;
        // for(int i =0; i!=resultPoint.size(); i++){
        //     cout<<resultPoint[i][0]<<"/"<<resultPoint[i][1]<<endl;
        // }
        // cout<<"resultPoint endl"<<endl;
        if(!resultPoint.empty()){
            int x = resultPoint.back()[0];
            int y = resultPoint.back()[1];
            resultPoint.pop_back();
            cout<<resultPoint[0][1]<<endl;

            while(!resultPoint.empty()){

                if(x>resultPoint.back()[0]){
                    x = resultPoint.back()[0];
                    y = resultPoint.back()[1];
                    resultPoint.pop_back();
                                cout<<x<<y<<endl;


                }
                else if(x == resultPoint.back()[0]){
                    if(y>resultPoint.back()[1]){
                        x = resultPoint.back()[0];
                        y = resultPoint.back()[1];
                        resultPoint.pop_back();
                    }else{
                        resultPoint.pop_back();
                    }
                }
                else if(x<resultPoint.back()[0])
                {
                    resultPoint.pop_back();
                }
            }
                                cout<<"연산끝"<<endl;

        vector<int> temp;
        temp.push_back(x);
        temp.push_back(y);
        resultPoint.push_back(temp);
        // cout<<resultPoint[0][0]<<endl;
        }

        if(resultPoint.empty()){
            cout<<"false"<<endl;
        }
        else{
            cout<<resultPoint.back()[0]<<" "<<resultPoint.back()[1]<<endl;
            resultPoint.pop_back();
        }
    }
};




int main() {
	int T,M,N;

	cin>>T>>M>>N;
    vector<string> wordList;
    char arr[31][31]={'0',};
    string data;
    string word;
    for(int i =0; i!=M; i++){
        cin>>data;

        for(unsigned int j=0; j!=data.length();j++){
            arr[i][j]=tolower(data[j]);
        }
    }
    for(int i=0; i!=T; i++){

        cin>>word;
        for(auto &it:word){
            it= tolower(it);
        }
        wordList.push_back(word);
    }

    for(auto &it :wordList){
        Bingo bg(it,M,N,arr);

        bg.search();
    }





	return 0;
}
