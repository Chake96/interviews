#include <stack>
#include <vector>
#include <cstddef>
#include <variant>
#include <queue>
#include <unordered_set>
#include <limits>
#include <algorithm>
#include <queue>
#include <numeric>

template<typename T>
struct Node{
    T val;
    Node* next{nullptr};
};

template<typename CordType = int>
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
    std::vector<AdjNode*> adj_list{};
};

using adj_list = std::vector<std::pair<int,int>>;

void dijkstras(const adj_list& lst){

}

using cost_or_path = std::variant<size_t, std::vector<size_t>>;

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
    std::vector<size_t> min_path{};
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


using cost_path_or_cycles = std::variant<int, std::vector<int>, bool>;
using src_dst_cost = std::tuple<int,int,int>;
enum choose_return{COST, PATH, HAS_CYCLES};
cost_path_or_cycles bellman_ford(const std::vector<src_dst_cost>& graph, int node_count, int start, int dest, choose_return return_type = choose_return::COST){
    
    static constexpr int init_val = std::numeric_limits<int>::max();
    cost_path_or_cycles result{};
    if(graph.empty()){
        return move(result);
    }
    std::vector<int> costs(node_count, init_val), parents(node_count);
    std::iota(begin(parents), end(parents), 0);
    costs[start] = 0; 
    for(auto i = 0; i < node_count-1; i++){
        bool any_changed = false;
        for(auto& edge: graph){
            auto src = std::get<0>(edge), dst = std::get<1>(edge), cst = std::get<2>(edge);
            if(costs[src] != init_val && costs[dst] > costs[src] + cst){
                costs[dst] = cst + costs[src];
                parents[dst] = src;
                any_changed = true;
            }
        }
        if(!any_changed) break;
    }
    for(auto& edge: graph){
        auto src = std::get<0>(edge), dst = std::get<1>(edge), cst = std::get<2>(edge);
        if(costs[src] != init_val && costs[dst] > costs[src] + cst){
            result = true;
        }
    }
    if(result.index() != 2){
        if(return_type == choose_return::COST){
            result = costs[dest];
        }else{
            std::vector<int> path{};
            for(auto i = dest; i != start && parents[i] != i; i = parents[i]){
                path.push_back(i);
            }
            reverse(path.begin(), path.end());
            result = path;
        }
    }
    return move(result);
}


#include <cstdio>
namespace details{
    void _topo_util(std::vector<std::vector<size_t>>& graph, size_t vertex, std::stack<size_t>& stack, std::vector<bool>& visited){
        visited[vertex] = true;
        for(size_t v: graph[vertex]){
            if(!visited[v]){
                _topo_util(graph, v, stack, visited);
            }
        }
        stack.push(vertex);
    }

}

std::stack<size_t> topological(std::vector<std::vector<size_t>>& graph){
    std::stack<size_t> order{};
    std::vector<bool> visited(graph.size(), false);
    for(size_t i = 0; i < graph.size(); i++){
        if(!visited[i]){
            details::_topo_util(graph, i, order, visited);
        }
    }
    return std::move(order);
}

// int main(){
//     vector<src_dst_cost>  no_neg_cycle_graph{
//         {0,2,-5},
//         {1,2,3},
//         {3,1,-1},
//         {2,3, 4},
//         {3,0,-1}
//     };

//     int start{0}, end{3};
//    auto result = bellman_ford(no_neg_cycle_graph, 4, start, end, choose_return::COST);
//    auto handle_result = [&result, &start, &end]{
//        switch(result.index()){
//            case 2:
//                 std::cout << "Graph has " << ((std::get<2>(result))? "" : "no") << " cycles!\n";
//                 break;
//             case 1:
//                 std::cout << "Path from " << start << " to " << end << '\n';
//                 for(auto node: std::get<1>(result)){
//                     std::cout << node << ' ';
//                 }
//                 std::cout << "\n";
//                 break;
//            default:
//                 std::cout << "the cost of the Path from " << start << " to " << end << " is: " << std::get<0>(result) << '\n';
//        }
//    };
//    handle_result();

// }