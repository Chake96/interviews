#include <bits/stdc++.h>
using namespace std;

class MedianFinder {
    priority_queue<int> large{};
    priority_queue<int, vector<int>, std::greater<>> small{};
public:
    MedianFinder() = default;
    
    void addNum(int num) {
        large.push(num);
        small.push(large.top());
        large.pop();
        if(small.size() > large.size()){
            large.push(small.top());
            small.pop();
        }        
    }
    double findMedian() {
        if((large.size() + small.size()) & 1 == 1){
            return static_cast<double>(large.top());
        }
        return static_cast<double>(large.top() + small.top())/2.0;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

 int main(){
    MedianFinder* obj = new MedianFinder();
    for(auto num: {1,3,2,6,1}){
        obj->addNum(num);
        double param_2 = obj->findMedian();
        cout << param_2 << ' ';    
    }
    cout << '\n';
 }