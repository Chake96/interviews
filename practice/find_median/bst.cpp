#include <bits/stdc++.h>
using namespace std;

template<typename ValType = int>
struct Node{
    const ValType val;
    Node<ValType>* next{nullptr};
    Node<ValType>* prev{nullptr};
    Node<ValType>* left{nullptr};
    Node<ValType>* right{nullptr};

    void add(Node<ValType>* node){
        if(node->val > val){
            if(right){
                right->add(node);
            }else{
                this->right = node;
                node->prev = this;
                node->next = this->next;
                if(this->next){
                    this->next->prev = node;
                }
                this->next = node;
            }
        }else{
            if(left){
                left->add(node);
            }else{
                this->left = node;
                node->next = this;
                node->prev = this->next;
                if(this->prev){
                    this->prev->next = node;
                }
            }
            this->prev = node;
        }
    }
};

using NT = Node<float>;


class MedianFinder {
    NT* root{nullptr};
    NT* median{nullptr};
    size_t count{0};
    bool count_odd{false};
public:
    MedianFinder() = default;
    
    void addNum(int num) {
        auto* temp = new NT{static_cast<float>(num)};
        count += 1;
        count_odd = !count_odd;
        if(!root){
            root = temp;
            median = temp;
        }else{
            root->add(temp);
            if(count_odd){
                if(num >= median->val){
                    median = median->next;
                }
            }else{
                if(num <= median->val){
                    median = median->prev;
                }

            }
        }
    }
    double findMedian() {
        if(count_odd){
            return median->val;
        }else{
            return (median->val + (median->next->val))/2.0;
        }
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
    for(auto num: {1, 3,2,6,1}){
        obj->addNum(num);
        double param_2 = obj->findMedian();
        cout << param_2 << ' ';    
    }
 }