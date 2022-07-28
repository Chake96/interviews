#include "numbers.h"

int main(){
    for(size_t k = 1; k < 10; k++){
        auto& triangle = pascals(k);
        for(size_t i = 0; i < k; i++){
            for(size_t j = 0; j < i; j++){
                std::cout << triangle[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
}