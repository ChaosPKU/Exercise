/*
Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

For example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.
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
    private:
      TrieNode *root;
    public:
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
        if(begin >= word.size()) return root->isEnd;
        if(word[begin] == '.')
          for(int i = 0;i < 26; ++ i)
            if(DFS(root->children[i], word, begin + 1))
              return true;
        else
          return DFS(root->children[word[begin] - 'a'], word, begin + 1);
        return false;
      }
      bool search(string word) {
        return DFS(root, word, 0);
      }
    };
