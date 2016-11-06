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

  return 0;
}
