#include <stack>
#include <vector>
#include <cstddef>
#include <variant>
#include <queue>
#include <limits>
#include <algorithm>
#include <priority_queue>

template<typename T>
struct Node{
    T val;
    *Node next{nullptr};
};

template<typename CoodType = int>
struct EuclideanCoords{
    CordType x{}, y{};
};


template<class Container> //could use type-traits or SFINAE to ensure at compile time the container has a .size() method
constexpr bool is_valid(const Container& container, size_t x, size_t y){
    return (x >= 0) && (y >= 0) && (container.size() > x) && (container.front().size() > y);
}


template<class Container>
std::queue<std::pair<size_t,size_t>> get_coords(const Container& container, size_t x, size_t y, bool eight_coords=false){
    std::queue<std::pair<size_t, size_t>> x_ys{};
    for(auto xs: {-1,0,1}){
        for(auto ys : {-1,0,1}){
            if((!eight_coords && abs(xs) == abs(y)) || (xs == 0 && ys == 0)){
                continue;
            }
            if(is_valid(x+xs, y+ys)){
                x_ys.push({x+xs, y+ys});
            }
        }
    }
    return x_ys;
}

template<typename T = int>
struct AdjNode{
    T val{};
    std::vector<AdjNode*> adj_list{}
};

using adj_list = std::vector<std::pair<int,int>>;

void dijkstras(const adj_list& lst){

}

using cost_or_path = std::variant<size_t, vector<size_t>>;

void create_path(std::vector<size_t>& min_path, std::vector<size_t>& parents, size_t dest){
    if(parents[dest] != dest){
        create_path(min_path, parents, parents[dest]);
        min_path.push_back(dest);
    }
}

cost_or_path dijkstras(const std::vector<std::vector<std::pair<size_t, size_t>>>& graph, size_t start, size_t dest, bool return_cost = true){
    std::variant<size_t, std::vector<size_t>> result{};
    std::vector<size_t> costs(graph.size(), std::numeric_limits<size_t>::max());
    std::vector<size_t> parents(graph.size());
    std::iota(begin(parents), end(parents), 0);
    vector<size_t> min_path{};
    costs[start] = 0;

    using node_cost = std::pair<size_t, size_t>;
    std::priority_queue<node_cost, std::vector<node_cost>, std::greater<node_cost>> pq{};
    pq.emplace(0, start);//cost to start is always 0 
    while(!pq.empty()){
        auto current = pq.top().second, cost = pq.top().first;
        pq.pop();
        if(current == dest){
            if(return_cost){
                result = costs[current]; //return the minimum path cost
            }else{
                min_path.push_back(start);
                create_path(min_path, parents, dest);
                result = std::move(min_path);
            }
            return result;
        }
        for(auto& edge: graph[current]){
            auto next = edge.second, cost_to_next = edge.first;
            if(costs[next] > costs[current] + cost_to_next){
                parents[next] = current;
                costs[next] = costs[current] + cost_to_next;
                pq.emplace(costs[next], next);
            }
        }
    }
    return result;
}