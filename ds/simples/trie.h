#include <iostream>
#include <array>
#include <string>
#include <memory>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <cassert>

static constexpr size_t ENGLISH_ALPHA_SIZE = 26;


struct TrieNode final{
    bool is_word{false};
    std::map<char, std::shared_ptr<TrieNode>> postfix;
};

class Trie final{
    public: //vars

    public: // methods

        Trie(const std::string& first_word): _word_count(1){
                this->insert(first_word);
        }
        Trie() noexcept = default;

        void insert(const std::string& word){
            _word_count += 1;
            auto current = _root;
            max_word_length = std::max(max_word_length, word.length());
            for_each(cbegin(word), cend(word), [&](char c){
                if(current->postfix.count(c) == 0){
                    current->postfix[c] = std::make_shared<TrieNode>();
                }
                current = current->postfix[c];
            });
            current->is_word = true;
        }

        bool search(const std::string& word){
            if(word.size() > max_word_length || word.empty()) return false;
            auto current = _root;
            bool found{true};
            std::for_each(word.cbegin(), word.cend(), [&](auto c){
                if(current->postfix.count(c) == 0){
                    found = false;
                }
                current = current->postfix[c];
            });
            return (found && current->is_word);
        }

        bool prefix(const std::string& word){
            if(word.size() > max_word_length || word.empty()) return false;
            auto current = _root;
            bool found{true};
            std::for_each(word.cbegin(), word.cend(), [&](auto c){
                if(current->postfix.count(c) == 0){
                    found = false;
                }
                current = current->postfix[c];
            });
            return found;
        }

    private: //vars
        std::shared_ptr<TrieNode> _root = std::make_shared<TrieNode>();
        size_t _word_count{0};
        size_t max_word_length{0};

};


// int main(){
//     Trie t1("first"), t2{};
//     assert(t1.search("first"));
//     assert(t1.search("firs") == false);
//     assert(t1.prefix("firs"));
//     assert(t2.search("anything") == false);
//     assert(t2.prefix("") == false);
// }