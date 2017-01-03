/*

Write a function to generate the generalized abbreviations of a word.

Example:
Given word = "word", return the following list (order does not matter):
["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]

*/

class Solution {
public:
    void backtracking(vector<string> &res, string &word, string &s, int b, int last){
        if(b == word.size()){
            res.push_back(s);
            return;
        }1
        string tmp = s;
        if(!last)
            for(int i = word.size() - 1;i >= b; -- i){
                s += to_string(i - b + 1);
                backtracking(res, word, s, i + 1, 1);
                s = tmp;
            }
        backtracking(res, word, s += word[b], b + 1, 0);
        s = tmp;
    }
    vector<string> generateAbbreviations(string word) {
        vector<string> res;
        string s = "";
        backtracking(res, word, s, 0, 0);
        return res;
    }
};
