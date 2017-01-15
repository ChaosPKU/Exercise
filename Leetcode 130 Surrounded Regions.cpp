/*
Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,
X X X X
X O O X
X X O X
X O X X
After running your function, the board should be:

X X X X
X X X X
X X X X
X O X X
*/

class Solution {
private:
    int m = 0, n = 0;
    void Walk(int x, int y, vector<vector<char> > &board){
        if(board[x][y] == 'O'){
            board[x][y] = '1';
            if(y + 1 < m) Walk(x, y + 1, board);
            if(y > 1)     Walk(x, y - 1, board);
            if(x + 1 < n) Walk(x + 1, y, board);
            if(x > 1)     Walk(x - 1, y, board);
        }
    }
public:
    void solve(vector<vector<char>>& board) {
        if(board.empty()) return;
        n = board.size();
        m = board[0].size();
        for(int i = 0;i < m; ++ i){
            Walk(0, i, board);
            Walk(n - 1, i, board);
        }
        for(int i = 1;i < n - 1; ++ i){
            Walk(i, 0, board);
            Walk(i, m - 1, board);
        }
        for(int i = 0;i < n; ++ i)
            for(int j = 0;j < m; ++ j){
                if(board[i][j] == 'O') board[i][j] = 'X';
                if(board[i][j] == '1') board[i][j] = 'O';
            }
    }
};
