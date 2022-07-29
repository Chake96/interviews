#include <bits/stdc++.h>

using namespace std;


using count_or_boards = variant<size_t, vector<vector<string>>>;
count_or_boards solveNQueens(int n, bool boards = true){
    count_or_boards result;
    if(boards){
        using vvs = vector<vector<string>>;
        vvs boards{};
        vector<string> board(n , string(n, '.'));
        set<int> cols{}, pos_diag{}, neg_diag{};
        std::function<void (size_t row)> back_track = [&](size_t row){
            if(row == n){
                boards.push_back(board);
                // board = vector<string>(n , string(n, '.'));
            }else{
                for(size_t i = 0; i < n; i++){
                    if(cols.count(i) == 0 && pos_diag.count(row+i) == 0 && neg_diag.count(row - i) == 0){
                        board[row][i] = 'Q';
                        cols.insert(i);
                        pos_diag.insert(row+i);
                        neg_diag.insert(row-i);

                        back_track(row+1);
                        
                        cols.erase(i);
                        pos_diag.erase(row+i);
                        neg_diag.erase(row-i);
                        board[row][i] = '.';
                    }
                }
            }
        };

        //set up stores of backtrack information
        
        //iterate through each row and try and place a queen
        back_track(0);
        result = boards;
    }else{
        size_t count = 0;
        vector<string> board(n , string(n, '.'));
        set<int> cols{}, pos_diag{}, neg_diag{};
        std::function<void (size_t row)> back_track = [&](size_t row){
            if(row == n){
                count += 1;
            }else{
                for(size_t i = 0; i < n; i++){
                    if(cols.count(i) == 0 && pos_diag.count(row+i) == 0 && neg_diag.count(row - i) == 0){
                        board[row][i] = 'Q';
                        cols.insert(i);
                        pos_diag.insert(row+i);
                        neg_diag.insert(row-i);

                        back_track(row+1);
                        
                        cols.erase(i);
                        pos_diag.erase(row+i);
                        neg_diag.erase(row-i);
                        board[row][i] = '.';
                    }
                }
            }
        };
        back_track(0);
        result = count;
    }

    return result;
}


int main(int argc, char** args){
    auto boards = std::get<1>(solveNQueens(4));
    bool print{false};
    if(argc > 1){
        print = true;
    }
    if(print){
        for(auto& board: boards){
            for(auto& str: board){
                cout << str << ' ';
            }
            cout << '\n';
        }
    }
    auto expected_boards = vector<vector<string>>{{".Q..","...Q","Q...","..Q."},{"..Q.","Q...","...Q",".Q.."}};
    size_t expected_count = 2;
    assert(boards == expected_boards);
    auto count = std::get<0>(solveNQueens(4, false));
    assert(count == expected_count);
    expected_count = 1;
    count = std::get<0>(solveNQueens(1, false));
    assert(count == expected_count);
    return EXIT_SUCCESS;
}