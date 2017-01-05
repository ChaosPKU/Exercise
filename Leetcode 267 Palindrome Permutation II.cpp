/*
Given a string s, return all the palindromic permutations (without duplicates) of it. Return an empty list if no palindromic permutation could be form.

For example:

Given s = "aabb", return ["abba", "baab"].

Given s = "abc", return [].

Hint:

If a palindromic permutation exists, we just need to generate the first half of the string.
To generate all distinct permutations of a (half of) string, use a similar approach from: Permutations II or Next Permutation.
*/

class Solution {
public:
    void genPermutations(vector<string> &res, string &s, string &m, int b){
        if(b >= s.size()){
            string tmp = s;
            reverse(tmp.begin(), tmp.end());
            s = s + m + tmp;
            res.push_back(s);
            return;
        }
        for(int i = b;i < s.size(); ++ i){
            if(i == b || s[i] != s[b]){
                string tmp = s;
                swap(s[b], s[i]);
                genPermutations(res, s, m, b + 1);
                s = tmp;
            }
        }
    }
    vector<string> generatePalindromes(string s) {
        vector<string> res;
        unordered_map<char, int> udmp;
        for(char c : s)
            udmp[c] ++ ;
        int nums = 0;
        string str = "";
        for(auto p : udmp)
            if((nums += (p.second % 2)) > 1) return res;
        string mid = "";
        for(auto p : udmp){
            if(p.second & 1) mid = string(1, p.first);
            str += string(p.second / 2, p.first);
        }
        genPermutations(res, str, mid, 0);
        return res;
    }
};
