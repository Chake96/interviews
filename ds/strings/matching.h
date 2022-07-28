//time: O*(len(S) + len(T))
//Rabin-Karp Algorithm for String Matching
//based on hashing

/*  input:
        S - pattern
        T - text
    intution
    1. hash the pattern, S
    2. calculate hashes for all prefixs of T
    3. compare each substring, len(S), against T
*/
#include <vector>
#include <string>
#include <string_view>
#include <functional>
#include <optional>

template<typename T>
using vec = std::vector<T>;

using str = std::string;

vec<size_t> knuth_morris_pratt(const std::string_view text, std::string_view pattern){
    //Time: O(N+M), Space: O(M)
    if(pattern.empty() || text.empty()) return {};
    static auto longest_prefix_suffix = [](const std::string_view patt) -> vec<size_t>{
        /* building a table of positions to refer to when we search the string
            if pattern = 'aaab' then -> [0,1,2,0];
            eg: search 'aaacdaaab' we'd get to 'c' -> use the table to look up where to reset our pattern to, and then look at 'd'
            prevents unccessary backtracking
        */
        vec<size_t> lps(patt.size(), 0);
        size_t patt_i = 1, prev_lps = 0;
        while(patt_i < patt.size()){
            if(patt[patt_i] == patt[prev_lps]){ //last prefix matches newest suffix, so we are extending our longest (with the +1)
                lps[patt_i] = prev_lps + 1; //extend from last largest
                prev_lps += 1;
                patt_i += 1;
            }else if(prev_lps == 0){
                patt_i += 1;
            }else{
                prev_lps = lps[prev_lps -1];
            }
        }
        return lps;
    };
    vec<size_t> indexs{};
    auto lps = longest_prefix_suffix(pattern);
    size_t text_i{0}, patt_i{0};
    while(text_i < text.size()){
        if(text[text_i] == pattern[patt_i]){
            text_i += 1;
            patt_i += 1;
        }else if(patt_i == 0){
            text_i += 1;
        }else{
            patt_i = lps[patt_i - 1];
        }
        if(patt_i == pattern.size()){
            indexs.push_back(text_i - pattern.size());
        }
    }
    return move(indexs);
}


auto kmp = [](auto&&... args) -> auto{
    return knuth_morris_pratt(std::forward<decltype(args)>(args)...);
};


template<class StrategyApplicator>
bool rabin_karp(const str& pattern, const str& text, StrategyApplicator func){ //returns false if no occurences were found
    const int plen = static_cast<int>(pattern.length()), tlen = static_cast<int>(text.length()); 
    auto phash = std::hash<str>{}(pattern);
    bool found{false};
    for(size_t i{0}; i < tlen - plen; i++){
        auto curr_hash = std::hash<str>{}(text.substr(i, 1));
        if(curr_hash == phash){
            found = true;
            func(i);
        }
    }
    return found;
}

template<size_t ALPHA_SIZE>
std::optional<ssize_t> boyer_moore(const std::string& text, const std::string& pattern){
    std::array<int, ALPHA_SIZE> bad_char_heuristic;
    for(size_t i = 0; i < ALPHA_SIZE; i++){
        bad_char_heuristic[text[i] - 'a'] = i;
    };

    ssize_t text_shift{0};
    const ssize_t t_sz{static_cast<ssize_t>(text.size())}, p_sz{static_cast<ssize_t>(pattern.size())};
    while(text_shift <= (t_sz - p_sz)){
        ssize_t pattern_idx{p_sz - 1};
        while(pattern_idx >= 0 && pattern[pattern_idx] == text[text_shift + pattern_idx]){
            pattern_idx -= 1;
        }
        if(pattern_idx < 0){
            return std::make_optional(text_shift);
        }else{
            text_shift += std::max(ssize_t(1), pattern_idx - bad_char_heuristic[text[text_shift + pattern_idx]]);
        }
    }
    return std::nullopt;
}
