/*

Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

For example,
Given words = ["oath","pea","eat","rain"] and board =

[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]
Return ["eat","oath"].
Note:
You may assume that all inputs are consist of lowercase letters a-z.

*/

class TrieNode{
    public:
      char val;
      TrieNode *children[26];
      bool isEnd;
      TrieNode(){
        isEnd = false;
        for(int i = 0;i < 26; ++ i)
          children[i] = NULL;
      }
      TrieNode(char _val){
        isEnd = false;
        for(int i = 0;i < 26; ++ i)
            children[i] = NULL;
        val = _val;
      }
    };

class WordDictionary {
    public:
      TrieNode *root;
      WordDictionary(){
        root = new TrieNode();
      }

      void addWord(string word) {
        TrieNode *ptr = root;
        for(int i = 0;i < word.size(); ++ i){
          if(!ptr->children[word[i] - 'a'])
            ptr->children[word[i] - 'a'] = new TrieNode(word[i]);
          ptr = ptr->children[word[i] - 'a'];
        }
        ptr->isEnd = true;
      }
      bool DFS(TrieNode *root, const string &word, int begin){
        if(!root) return false;
        if(begin > word.size()) return root->isEnd;
        if(word[begin] == '.')
          for(int i = 0;i < 26; ++ i){
            if(DFS(root->children[i], word, begin + 1))
              return true;
          }
        else
          return DFS(root->children[word[begin] - 'a'], word, begin + 1);
        return false;
      }
      bool search(string word) {
        return DFS(root, word, 0);
      }
    };
    
class Solution {
private:
    unordered_map<char, vector<pair<int, int>>> m;
    int height = 0, width = 0;
    int dx[4] = {1,-1,0,0}, dy[4] = {0,0,1,-1};
    void backtracking(TrieNode *root, const vector<vector<char>>& board, vector<vector<bool>>& visited, string &s, set<string> &res, int x, int y){
        if(!root || root->val != board[x][y])
            return;
        s.push_back(board[x][y]);
        if(root->isEnd){
            res.insert(s);
        }
        visited[x][y] = 1;
        for(int i = 0;i < 4; ++ i){
            int xx = x + dx[i], yy = y + dy[i];
            if(xx < 0 || yy < 0 || xx >= height || yy >= width || visited[xx][yy])
                continue;
            backtracking(root->children[board[xx][yy] - 'a'], board, visited, s, res, xx, yy);
        }
        s.pop_back();
        visited[x][y] = 0;
    }
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        WordDictionary *w = new WordDictionary();
        set<string> res;
        m.clear();
        if(board.empty()) return vector<string>(res.begin(), res.end());
        height = board.size();
        width = board[0].size();
        for(int i = 0;i < words.size(); ++ i)
            w->addWord(words[i]);
        for(int i = 0;i < height; ++ i)
            for(int j = 0;j < width; ++ j){
                m[board[i][j]].push_back(make_pair(i, j));
            }
        string s = "";
        for(int i = 0; i < 26; ++ i){
            auto alter = m.find('a' + i);
            if(alter == m.end()) continue;
            vector<pair<int, int>> v = alter->second;
            for(int j = 0;j < v.size(); ++ j){
                vector<vector<bool>> visited(height, vector<bool>(width, 0));
                backtracking(w->root->children[i], board, visited, s, res, v[j].first, v[j].second);
            }
        }
        return vector<string>(res.begin(), res.end());
    }
};
