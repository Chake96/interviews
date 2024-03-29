#include <bits/stdc++.h>


template<typename Integer = int>
const std::vector<std::vector<Integer>>& pascals(size_t n){
    static std::vector<std::vector<Integer>> triangle(n, std::vector<Integer>(n, {}));
    static bool init{false};
    static size_t max_n = 3;
    //TODO: fix this by preallocating twice, allocation of rows should be previous row_size + 1,
    // then fill in first and last with 1



    if(n > triangle.capacity() || !init){
        auto triangle_cap = triangle.capacity();
        triangle.resize(n*2, std::vector<int>(n));
        for(; triangle_cap < triangle.capacity(); triangle_cap++){
            triangle[triangle_cap][0] = 1;
            triangle[triangle_cap][triangle_cap] = 1;
        }
    }
    if(n < 3){
        triangle = {
            {1},{1, 1}
        };
        return triangle;
    }
    if(!init){
        init = true;
        triangle[0][0] = 1;
        triangle[1][0] = 1;
        triangle[1][1] = 1;
        for(size_t row = 2; row < n; row++){
            for(size_t i = 0; i <= row; i++){
                triangle[row][i] = triangle[row-1][i-1] + triangle[row-1][i];
            }
        }
    }else if(n > max_n){
        for(size_t row = max_n-1; max_n < n; row++){
            for(auto i = 0; i <= row; i++){
                triangle[row][i] = triangle[row-1][i-1] + triangle[row-1][i];
            }
        }
        max_n = n;

    }
    return triangle;
} 

