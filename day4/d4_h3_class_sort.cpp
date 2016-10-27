#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;


tuple <long long,long long> fib(long long n, long long mod){
    if(n==0){
        return make_tuple(0,1);
    }
    long long a, b, c ,d = 0;

    tie(a,b) = fib( n/2, mod );
    long long temp;
    temp = b*2-a;
    while(temp<0){
        temp += mod;
    }
    c = a*(temp);
    d = a*a+b*b;
    if(n%2==0){
        return make_tuple(c%mod, d%mod);
    }
    else{
        return make_tuple(d%mod, (c%mod+d%mod)%mod);
    }
}


int main(){
    long long mod;
    long long number;
    long long answer;
    long long temp;
    vector<long long> N1;
    vector<long long> N2;
    int M1,M2;

    cin>>mod;
    cin>>M1;
    for(int i=0; i!=M1; i++){
        cin>>number;
        tie(answer,temp) = fib(number,mod);
        N1.push_back(answer);
    }

    cin>>M2;
    for(int i=0; i!=M2; i++){
        cin>>number;
        tie(answer,temp) = fib(number,mod);
        N2.push_back(answer);
    }
// I initialized N2 but it is better to not save , just find in N1 in iteration.
    for(int i=0; i!=N2.size(); i++){
        if(find(N1.begin(), N1.end(),N2[i])!=N1.end()){
            cout<<N2[i]<<" : 1"<<endl;
        }
        else{
            cout<<N2[i]<<" : 0"<<endl;
        }
    }



    return 0;
}
