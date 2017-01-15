/*

Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z.

*/

class TrieNode {
public:
    // Initialize your data structure here.
    char val;
    bool isEnd;
    TrieNode *children[26];
    TrieNode() {
        isEnd = false;
        for(int i = 0;i < 26; ++ i)
            children[i] = NULL;
    }
    TrieNode(char _val) {
        val = _val;
        isEnd = false;
        for(int i = 0;i < 26; ++ i)
            children[i] = NULL;
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }
    
    // Inserts a word into the trie.
    void insert(string word) {
        TrieNode *ptr = root;
        for(int i = 0;i < word.size(); ++ i){
            if(ptr->children[word[i] - 'a'] == NULL){
                ptr->children[word[i] - 'a'] = new TrieNode(word[i]);
            }
            ptr = ptr->children[word[i] - 'a'];
        }
        ptr->isEnd = true;
    }
    
    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode *ptr = root;
        for(int i = 0;i < word.size(); ++ i){
            if(ptr->children[word[i] - 'a'] == NULL){
                return false;
            }
            ptr = ptr->children[word[i] - 'a'];
        }
        return ptr->isEnd;
    }
    
    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode *ptr = root;
        for(int i = 0;i < prefix.size(); ++ i){
            if(ptr->children[prefix[i] - 'a'] == NULL){
                return false;
            }
            ptr = ptr->children[prefix[i] - 'a'];
        }
        return true;
    }
    
private:
    TrieNode* root;
};
