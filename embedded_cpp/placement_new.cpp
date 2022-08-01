

using namespace std; //how to make other developers loathe you

#include <bits/stdc++.h> //horrible in real world
#include <stdio.h>

struct MyStruct{
        MyStruct() = default;
        MyStruct(string init_val):value(init_val){
        }
        string value{"The Default Value"};
};

template<class FactoryType, typename... TypeParams>
FactoryType* factory_placement_new(void* preallocd_mem, size_t index, TypeParams... params){
    FactoryType* new_inst = new(&preallocd_mem[index]) FactoryType(params...);
    return new_inst;
}


int main(){
    alignas(MyStruct) uint8_t struct_buffer[sizeof(MyStruct)*2];
    alignas(uint32_t) uint8_t number_buffer[sizeof(uint32_t)*2];
    
    MyStruct* first = factory_placement_new<MyStruct>(struct_buffer, 0);
    MyStruct* second = factory_placement_new<MyStruct>(struct_buffer, 1);

    printf("First String: %s \n Second String: %s", first->value.c_str(), second->value.c_str());
    return EXIT_SUCCESS;
}