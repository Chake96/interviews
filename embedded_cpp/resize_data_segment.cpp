#include <unistd.h>
#include <cstdint>
#include <stdio.h>

int main(){
    int s1{0}, s2{0}, s3{0};

    void* current = sbrk(0);
    printf("%p\n", current);
    current = sbrk((intptr_t) ((char*)current+1));
    printf("%p\n", current);


    return 0;
}