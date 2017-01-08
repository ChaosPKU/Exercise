/*
A string such as "word" contains the following abbreviations:

["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]
Given a target string and a set of strings in a dictionary, find an abbreviation of this target string with the smallest possible length such that it does not conflict with abbreviations of the strings in the dictionary.

Each number or letter in the abbreviation is considered length = 1. For example, the abbreviation "a32bc" has length = 4.

Note:
In the case of multiple answers as shown in the second example below, you may return any one of them.
Assume length of target string = m, and dictionary size = n. You may assume that m ≤ 21, n ≤ 1000, and log2(n) + m ≤ 20.
Examples:
"apple", ["blade"] -> "a4" (because "5" or "4e" conflicts with "blade")

"apple", ["plain", "amber", "blade"] -> "1p3" (other valid answers include "ap3", "a3e", "2p2", "3le", "3l1").
*/


class Solution {
public:
    bool validWordAbbreviation(string &word, string &abbr) {
        int wlen = word.size(), alen = abbr.size(), wptr = 0, aptr = 0;
        while(wptr < wlen && aptr < alen){
            if(!isdigit(abbr[aptr]))
                if(word[wptr ++] != abbr[aptr ++])    return false;
                else continue;
            else{
                int num = abbr[aptr] - '0';
                if(num == 0) return false;
                while(isdigit(abbr[++ aptr]))   {
                    num = num * 10 + abbr[aptr] - '0';
                    if(num > wlen - wptr) return false;
                }
                while(num --) wptr ++;
            }
        }
        return wptr == wlen && aptr == alen;
    }
    void backtracking(vector<string> &dictionary, string &word, string &s, int b, int last, string &res, int &slen, int &rlen){
        if(b == word.size()){
            for(string str : dictionary)
                if(str.size() == word.size() && validWordAbbreviation(str, s))
                    return;
            res = s;
            rlen = slen;
            return;
        }
        string tmp = s;
        if(!last)
            for(int i = word.size() - 1;i >= b; -- i){
                s += to_string(i - b + 1);
                slen += 1;
                if(slen <= rlen) 
                    backtracking(dictionary, word, s, i + 1, 1, res, slen, rlen);
                s = tmp;
                slen -= 1;
            }
        slen += 1;
        if(slen < rlen) 
            backtracking(dictionary, word, s += word[b], b + 1, 0, res, slen, rlen);
        s = tmp;
        slen -= 1;
    }
    string minAbbreviation(string target, vector<string>& dictionary) {
        string s = "", res = target;
        int slen = 0, rlen = target.size();
        backtracking(dictionary, target, s, 0, 0, res, slen, rlen);
        return res;
    }
};

// From @https://discuss.leetcode.com/topic/61457/c-bit-manipulation-dfs-solution
class Solution {
    int n, cand, bn, minlen, minab;
    vector<int> dict;
    
    // Return the length of abbreviation given bit sequence
    int abbrLen(int mask) {
        int count = n;
        for (int b = 3; b < bn; b <<= 1)
            if ((mask & b) == 0)
                count --;
        return count;
    }

    // DFS backtracking
    void dfs(int bit, int mask) {
        int len = abbrLen(mask);
        if (len >= minlen) return;
        bool match = true;
        for (auto d : dict) {
            if ((mask & d) == 0) {
                match = false;
                break;
            }
        }
        if (match) {
            minlen = len;
            minab = mask;
        }
        else
            for (int b = bit; b < bn; b <<= 1)
                if (cand & b) dfs(b << 1, mask + b);
    }

public:
    string minAbbreviation(string target, vector<string>& dictionary) {
        n = target.size(), bn = 1 << n, cand = 0, minlen = INT_MAX;
        string res;
        
        // Preprocessing with bit manipulation
        for (auto w : dictionary) {
            int word = 0;
            if (w.size() != n) continue;
            for (int i = n-1, bit = 1; i >= 0; --i, bit <<= 1)
                if (target[i] != w[i]) word += bit;
            dict.push_back(word);
            cand |= word;
        }
        dfs(1, 0);

        // Reconstruct abbreviation from bit sequence
        for (int i = n-1, pre = i; i >= 0; --i, minab >>= 1) {
            if (minab & 1) {
                if (pre-i > 0) res = to_string(pre-i) + res;
                pre = i - 1;
                res = target[i] + res;
            }
            else if (i == 0) res = to_string(pre-i+1) + res;
        }
        return res;
    }
};
