/*
Given a set of words (without duplicates), find all word squares you can build from them.

A sequence of words forms a valid word square if the kth row and column read the exact same string, where 0 ≤ k < max(numRows, numColumns).

For example, the word sequence ["ball","area","lead","lady"] forms a word square because each word reads the same both horizontally and vertically.

b a l l
a r e a
l e a d
l a d y
Note:
There are at least 1 and at most 1000 words.
All words will have the exact same length.
Word length is at least 1 and at most 5.
Each word contains only lowercase English alphabet a-z.
Example 1:

Input:
["area","lead","wall","lady","ball"]

Output:
[
  [ "wall",
    "area",
    "lead",
    "lady"
  ],
  [ "ball",
    "area",
    "lead",
    "lady"
  ]
]

Explanation:
The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
Example 2:

Input:
["abat","baba","atan","atal"]

Output:
[
  [ "baba",
    "abat",
    "baba",
    "atan"
  ],
  [ "baba",
    "abat",
    "baba",
    "atal"
  ]
]

Explanation:
The output consists of two word squares. The order of output does not matter (just the order of words in each word square matters).
*/

// Trie Version
class TrieNode {
public:
    vector<int> indices;
    vector<TrieNode*> children;
    TrieNode(){
        children.resize(26, NULL);
    }
};
class Trie {
public:
    TrieNode *root;
    Trie(vector<string> &vtr){
        root = new TrieNode();
        root->indices.resize(vtr.size());
        for(int i = 0;i < vtr.size(); ++ i){
            root->indices[i] = i;
            TrieNode *tmp = root;
            for(int j = 0;j < vtr[i].size(); ++ j){
                if(!tmp->children[vtr[i][j] - 'a'])
                    tmp->children[vtr[i][j] - 'a'] = new TrieNode();
                tmp = tmp->children[vtr[i][j] - 'a'];
                tmp->indices.push_back(i);
            }
        }
    }
    vector<int>* getIndices(string prefix){
        TrieNode *tmp = root;
        for(int i = 0;i < prefix.size(); ++ i){
            if(!tmp) break;
            tmp = tmp->children[prefix[i] - 'a'];
        }
        return tmp ? &tmp->indices : NULL;
    }
};
class Solution {
public:
    vector<string> strs;
    vector<vector<string> > res;
    Trie *tree;
    int n;
    vector<vector<string>> wordSquares(vector<string>& words) {
        n = words[0].size();
        tree = new Trie(words);
        strs.resize(n);
        build(0, words);
        return res;
    }
    void build(int i, vector<string>& words){
        if(i == n){
            res.push_back(strs);
            return;
        }
        string prefix = "";
        for(int k = 0;k < i; ++ k)
            prefix += strs[k][i];
        vector<int> *vtr = tree->getIndices(prefix);
        if(!vtr) return;
        for(int k : *vtr){
            strs[i] = words[k];
            build(i + 1, words);
        }
    }
};

// HashMap Version
class Solution {
public:
    vector<string> strs;
    vector<vector<string> > res;
    unordered_map<string, vector<string> > udmp;
    int n;
    vector<vector<string>> wordSquares(vector<string>& words) {
        n = words[0].size();
        for(string word : words)
            for(int i = 0;i < n; ++ i)
                udmp[word.substr(0, i)].push_back(word);
        strs.resize(n);
        build(0);
        return res;
    }
    void build(int i){
        if(i == n){
            res.push_back(strs);
            return;
        }
        string prefix = "";
        for(int k = 0;k < i; ++ k)
            prefix += strs[k][i];
        for(string s : udmp[prefix]){
            strs[i] = s;
            build(i + 1);
        }
    }
};
