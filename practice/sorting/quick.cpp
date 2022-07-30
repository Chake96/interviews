#include <bits/stdc++.h>

using namespace std;


template<class Cont>
void sort(Cont& cont, ssize_t start, ssize_t end){
    if(start >= end || end >= cont.size()) return;
    function<ssize_t(ssize_t,ssize_t)> _sort = [&](ssize_t start, ssize_t end)->ssize_t{
        typename Cont::value_type piv = cont[start];
        size_t less_than_piv_count{0};
        for(auto i = start+1; i <= end; i++){
            if(cont[i] <= piv) less_than_piv_count += 1;
        }

        size_t piv_index = start + less_than_piv_count;
        swap(cont[piv_index], cont[start]);
        for(auto left = start, right = end; left < piv_index && right > piv_index; left++, right--){
            while(cont[left] <= piv) left += 1;
            while(cont[right] > piv) right -= 1;
            if(left < piv_index && right > piv_index){
                swap(cont[left], cont[right]);
            }
        }
        return piv_index;
    };

    ssize_t partition_point = _sort(start, end);
    sort(cont, start, partition_point-1);
    sort(cont, partition_point+1, end);
}

template<class Cont>
void print(const Cont& cont){
    for(auto v: cont){
        cout << v << ' ';
    }
    cout << '\n';
}


int main(){
    vector<int> a = {1,78,83,24,6};
    sort(a, 0, a.size()-1);
    print(a);
}