/*
Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:

Only one letter can be changed at a time
Each intermediate word must exist in the word list
For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
Return
  [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]
Note:
All words have the same length.
All words contain only lowercase alphabetic characters.
*/

class Solution {
private:
    bool searchLadders(unordered_set<string> &beginWords, unordered_set<string> &endWords, unordered_set<string> &wordList, unordered_map<string, vector<string> > &children, bool flip){
        flip = !flip;
        if(beginWords.empty()) return false;
        if(beginWords.size() > endWords.size())
            return searchLadders(endWords, beginWords, wordList, children, flip);
        unordered_set<string> middle;
        bool done = false;
        for(string word : beginWords){
            int n = word.size();
            string tmp = word;
            for(int i = 0;i < n; ++ i){
                for(int j = 0;j < 26; ++ j){
                    word[i] = j + 'a';
                    if(endWords.find(word) != endWords.end()){
                        done = true;
                        flip? children[word].push_back(tmp) : children[tmp].push_back(word);
                    }
                    else if(!done && wordList.find(word) != wordList.end()){
                        middle.insert(word);
                        flip? children[word].push_back(tmp) : children[tmp].push_back(word);
                    }
                }
                word = tmp;
            }
        }
        for(string word : middle)
            wordList.erase(word);
        return done || searchLadders(endWords, middle, wordList, children, flip);
    }
    void genLadders(string &begin, string &end, unordered_map<string, vector<string> >& children,vector<string>& cur, vector<vector<string> >& res){
        if(begin == end){
            res.push_back(cur);
            return;
        }
        for(string child : children[begin]){
            cur.push_back(child);
            genLadders(child, end, children, cur, res);
            cur.pop_back();
        }
    }
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordList) {
        vector<vector<string> > res;
        vector<string> cur;
        cur.push_back(beginWord);
        
        unordered_set<string> beginWords, endWords;
        beginWords.insert(beginWord);
        endWords.insert(endWord);
        wordList.erase(beginWord);
        wordList.erase(endWord);
        unordered_map<string, vector<string> > children;
        bool flip = true;
        
        if(searchLadders(beginWords, endWords, wordList, children, flip))
            genLadders(beginWord, endWord, children, cur, res);
        return res;
    }
};
