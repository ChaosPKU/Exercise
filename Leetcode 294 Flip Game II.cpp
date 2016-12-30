/*
You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -, you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move and therefore the other person will be the winner.

Write a function to determine if the starting player can guarantee a win.

For example, given s = "++++", return true. The starting player can guarantee a win by flipping the middle "++" to become "+--+".

Follow up:
Derive your algorithm's runtime complexity.
*/

class Solution {
public:
    //DFS()在递归深度为偶数的时候（starting player选择）表示必胜，在递归深度为奇数时（the other player选择）表示存在一种情况能胜，初始深度为0。
    bool canWin(string &s) {
        string tmp = s;
        for(int i = 0;i < (int)s.size() - 1; ++ i)
            if(s[i] == '+' && s[i + 1] == '+'){
                s[i] = s[i + 1] = '-';
                if(!canWin(s))
                    return true;
                s = tmp;
            }
        return false;
    }
};

/*
参考HDU 1848 Fibonacci again and again.cpp中的解释。
此题目也是一个Impartial Combinatorial Games(ICG)，所以可以用SG Function来做。
首先是将游戏分解，对于“++--++++--+”这样的字符串，可以用(2,4)表示(连续的长度大于2的‘+’组成的的字符串长度)。
对于单个的x，其sg函数满足以下性质(FMV表示FirstMissingNumber)：
1、x < 2，则g(x) = 0;
2、g(x) = FMV(g(0, N-2), g(1, N-3), g(2, N-4), ... , g(N/2-1, N-N/2-2)) = FMV(g(0)^g(N-2), g(1)^g(N-3), g(2)^g(N-4)), ... g(N/2-1, N-N/2-2));
可得题解：

int firstMissingNumber(unordered_set<int> lut) {
    int m = lut.size();
    for (int i = 0; i < m; ++i) {
        if (lut.count(i) == 0) return i;
    }
    return m;
}
bool canWin(string s) {
    int curlen = 0, maxlen = 0;
    vector<int> board_init_state;
    for (int i = 0; i < s.size(); ++i) {    
        if (s[i] == '+') curlen++;              // Find the length of all continuous '+' signs
        if (i+1 == s.size() || s[i] == '-') {
            if (curlen >= 2) board_init_state.push_back(curlen);    // only length >= 2 counts
            maxlen = max(maxlen, curlen);       // Also get the maximum continuous length
            curlen = 0;
        }
    }          // For instance ++--+--++++-+ will be represented as (2, 4)
    vector<int> g(maxlen+1, 0);    // Sprague-Grundy function of 0 ~ maxlen
    for (int len = 2; len <= maxlen; ++len) {
        unordered_set<int> gsub;    // the S-G value of all subgame states
        for (int len_first_game = 0; len_first_game < len/2; ++len_first_game) {
            int len_second_game = len - len_first_game - 2;
            // Theorem 2: g[game] = g[subgame1]^g[subgame2]^g[subgame3]...;
            gsub.insert(g[len_first_game] ^ g[len_second_game]);
        }
        g[len] = firstMissingNumber(gsub);
    }
    
    int g_final = 0;
    for (auto& s: board_init_state) g_final ^= g[s];
    return g_final != 0;    // Theorem 1: First player must win if g(current_state) != 0
 }
 
 复杂度由O(N!)降为O(N^2);
 */
