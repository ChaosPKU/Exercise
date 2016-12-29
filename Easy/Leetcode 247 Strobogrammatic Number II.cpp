/*
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Find all strobogrammatic numbers that are of length = n.

For example,
Given n = 2, return ["11","69","88","96"].
*/
//按深度DFS并决定退出条件，注意和3的不同
class Solution {
public:
    vector<string> findStrobogrammatic(int n, int depth){
        depth ++;
        if(n == 0) return {""};
        if(n == 1) return {"0", "1", "8"};
        vector<string> tmp = findStrobogrammatic(n - 2, depth + 1), res;
        const static vector<string> str({"0", "0", "1", "1", "6", "9", "8", "8", "9", "6"});
        for(int i = (depth == 1); i < str.size() / 2; ++ i)
            for(string s : tmp)
                res.push_back(str[2 * i] + s + str[2 * i + 1]);
        return res;
    }
    vector<string> findStrobogrammatic(int n) {
        return findStrobogrammatic(n, 0);
    }
};
