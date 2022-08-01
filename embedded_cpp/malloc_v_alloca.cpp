
#include <cstdint>
#include <malloc.h>
#include <alloca.h>

int main(){
    uint8_t* buf1;
    buf1 = (uint8_t*) malloc(sizeof(int)*2);
    if(buf1){
        buf1[0] = 1;
        buf1[1] = 2;
        printf("%d %d\n", buf1[0], buf1[1]);
    }
    free(buf1);

    uint8_t* buf2;
    buf2 = (uint8_t*) alloca(sizeof(int)*2);
    if(buf2){
        buf2[0] = 3;
        buf2[1] = 4;
        printf("%d %d\n", buf2[0], buf2[1]);
    }
}