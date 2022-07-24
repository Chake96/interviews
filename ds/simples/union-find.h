#include <vector>
#include <stdio.h>
#include <limits>

class UnionFind final{
    static constexpr int min_int = std::numeric_limits<int>::min();
    public:

        UnionFind() = delete;

        UnionFind(size_t size, int def = min_int): parents(size, def), ranks(size, 0){
        }

        int find_parent(int value){
            if(parents[value] != min_int){
                return find_parent(parents[value]);
            }else{
                return value;
            }
        }

        bool union_parents(int x, int y){
            int xpar = find_parent(x), ypar = find_parent(y);
            if(xpar == ypar){
                return false;
            }else if(ranks[xpar] < ranks[ypar]){
                parents[xpar] = ypar;
            }else if(ranks[xpar] > ranks[ypar]){
                parents[ypar] = xpar;
            }else{
                parents[ypar] = xpar;
                ranks[xpar] += 1;
            }
            return true;
        }

    private:
        std::vector<int> parents, ranks;
};