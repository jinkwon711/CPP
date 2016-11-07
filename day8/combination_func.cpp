#include <iostream>
#include <vector>
using namespace std;  


void go(int offset, int k) { k 대신 단어수.즉 temp.size()
        if (k == 0) {
          pretty_print(combination);
          return;
        }
        for (int i = offset; i <= temp1.size() - k; ++i) {
          combination.push_back(people[i]);
          go(i+1, k-1);
          combination.pop_back();
        }
      }


int main(){

  //원하는것이 스트링이 있는 벡터를 넣으면 벡터의 요소끼리

  return 0;
}
