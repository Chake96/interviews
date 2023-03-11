#include <bits/stdc++.h>
#include <cstdio>


using namespace std;



int main(){
    vector<int> example = {1,2,3,4,5,6,7,8,9,10};

    for(auto it = example.begin(); it != example.end(); it++){
        if(*it == 2){
            cout << *it << '\n';
        }
    }


    return 0;
}