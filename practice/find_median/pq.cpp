#include <bits/stdc++.h>
using namespace std;

class MedianFinder {
    priority_queue<int> large{};
    priority_queue<int, vector<int>, std::less<>> small{};
    size_t count{0};
    bool count_odd{false};
public:
    MedianFinder() = default;
    
    void addNum(int num) {
        count += 1;
        count_odd = !count_odd;
        large.push(num);
        small.push(large.top());
        large.pop();
        if(small.size() > large.size()){
            large.push(small.top());
            small.pop();
        }
    }
    double findMedian() {
        if(large.size() > small.size()) return large.top();
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