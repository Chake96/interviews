

#include <bits/stdc++.h>

using namespace std; //bad in production/real software
vector<int> countBits(int n){
    vector<int> results(n+1, 0);
    for(int i = 1; i < n+1; i++){
        results[i] = results[i/2] + i % 2;
    }
    // result[]
    return move(results);
}


int main(int argc, char** argv){
    int n = 100;
    if(argc > 1){
        n = atoi(argv[1]);
    }
    const int m = n;
    for(auto num_bits: countBits(n)){
        printf("Num Set Bits in %d: %d\n", m - n--, num_bits);
    }
}