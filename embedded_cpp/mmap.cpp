#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


int main(){
    int f_d = 0;
    struct stat file_stat;
    f_d = open("The Restaurant at the End of the Universe.txt", O_RDWR);
    if(f_d == -1){
        return EXIT_FAILURE;
    }

    if(fstat(f_d, &file_stat)){
        printf("\nfstat error: [%s]\n", strerror(errno));
        close(f_d);
        return EXIT_FAILURE;
    };

    char* file_in_mem = static_cast<char*>(mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, f_d, 0));
    for(int i = 0; i < file_stat.st_size; i++){
        printf("%c", file_in_mem[i]);
    }
    printf("\n");

    //clean up memory
    munmap(file_in_mem, file_stat.st_size);
    close(f_d);

    return EXIT_SUCCESS;
}