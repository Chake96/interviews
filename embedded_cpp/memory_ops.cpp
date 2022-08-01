

//malloc, free
//new,  delete
//mmap
#include <type_traits>
#include <bits/stdc++.h> //bad in prod
using namespace std; //bad in prod


struct dl_node{
    dl_node* prev{nullptr}, *next{nullptr};
};


struct alloc_block{
    dl_node* node;
    size_t size{0};
    char* block;  
};