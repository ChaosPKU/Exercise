/*
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.



Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
*/

class Solution {
public:
        void mPermutation(vector<vector<string>> &res, vector<int> &emt,vector<bool> &pos, vector<bool> &neg, int n, int i){
        if(n == i){
            vector<string> str;
            for(int x = 0;x < n; ++ x){
                string s = "";
                for(int y = 0;y < n; ++ y){
                    if(y != emt[x])
                        s += '.';
                    else{
                        s += 'Q';
                    }
                }
                str.push_back(s);
            }
            res.push_back(str);
            return;
        }
        for(int j = i;j < n; ++ j){
            swap(emt[i],emt[j]);
            if(!pos[i + emt[i]] && !neg[n - 1 + i - emt[i]]){
                pos[i + emt[i]] = neg[n - 1 + i - emt[i]] = true;
                mPermutation(res, emt, pos, neg, n, i + 1);
                pos[i + emt[i]] = neg[n - 1 + i - emt[i]] = false;
            }
            swap(emt[i],emt[j]);
        }
    }
    vector<vector<string>> solveNQueens(int n)  {
        vector<vector<string>> res;
        vector<int> emt;
        vector<bool> pos,neg;
        for(int i = 0;i < n; ++ i){
            emt.push_back(i);
        }
        for(int i = 0;i < 2 * n - 1; ++ i){
            pos.push_back(false);
            neg.push_back(false);
        }
        mPermutation(res, emt, pos, neg, n, 0);
        return res;
    }
};
