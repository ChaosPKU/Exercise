#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

struct TreeNode{
    float val;
    char crt;
    string encodeStr;
    TreeNode *left, *right;
    TreeNode(float v, char c){
        this->val = v;
        this->left = this->right = NULL;
        this->crt = c;
    }
    TreeNode(float v, TreeNode *l, TreeNode *r){
        this->val = v;
        this->left = l;
        this->right = r;
        this->crt = '$';
    }
};

bool NodeCmp(const TreeNode* a, const TreeNode* b){
    return a->val > b->val;
}

struct HuffmanTree{
    TreeNode* root;
    unordered_map<char, string> encoding;
    HuffmanTree(){this->root = NULL;}
    void genTree(const unordered_map<char, float> &udp){
        cout << "构造Huffman树..." << endl;
        int n = (int)udp.size();
        if(!n) return;
        if(n == 1){
            this->root = new TreeNode(udp.begin()->second, udp.begin()->first);
            return;
        }
        priority_queue<TreeNode*, vector<TreeNode*>, decltype(&NodeCmp)> q(NodeCmp);
        for(auto iter = udp.begin(); iter != udp.end(); ++ iter)
            q.push(new TreeNode(iter->second, iter->first));

        while(!q.empty()){
            TreeNode* a = q.top();
            q.pop();
            TreeNode* b = q.top();
            q.pop();
            if(q.empty()){
                this->root = new TreeNode(0, a, b);
                break;
            }
            q.push(new TreeNode(a->val + b->val, a, b));
        }
        this->getEncodingStr();
        return ;
    }
    void DFS(TreeNode* root, int &res, string &s, int &cnt, int &path){
        if(!root) return;
        if(!root->left && !root->right){
            cnt += root->val;
            res += path * (root->val);
            root->encodeStr = s;
            encoding[root->crt] = root->encodeStr;
            cout << root->crt << ": " << root->encodeStr << endl;
            return ;
        }

        s.push_back('0');
        DFS(root->left, res, s, cnt, ++ path);
        -- path;
        s.pop_back();

        s.push_back('1');
        DFS(root->right, res, s, cnt, ++ path);
        -- path;
        s.pop_back();
    }
    void getEncodingStr(){
        cout << "获取各字符编码:" << endl;
        if(!root) return ;
        if(!root->left && !root->right){
            encoding[root->crt] = '0';
            return ;
        }
        string s = "";
        int res = 0, cnt = 0, path = 1;
        s = "0";
        DFS(root->left, res, s, cnt, path);
        s = "1";
        DFS(root->right, res, s, cnt, path);
    }
    float getAverageEnCodeLength(const unordered_map<char, float> &udp){
        cout << "平均编码长度为:" << endl;
        int sum = 0, cnt = 0;
        for(auto iter = udp.begin(); iter != udp.end(); ++ iter){
            cnt += iter->second;
            sum += iter->second * encoding[iter->first].size();
        }
        return (float)sum / cnt;
    }
    string getLeastEncoding(const string &s){
        cout << "依据最短编码转码:" << endl << s << endl;
        string res = "";
        for(char c : s)
            res += encoding[c] + " ";
        res.pop_back();
        return res;
    }
};

// 依据词频构造哈希表
unordered_map<char, float> construct(vector<char> word, vector<float> freq){
    unordered_map<char, float> udp;
    int n = (int)word.size();
    for(int i = 0; i < n; ++ i)
        udp[word[i]] = freq[i];
    return udp;
};

int main(){
    string input="aabbbbbcccccccdddd";
    unordered_map<char, float> udp;
    for(char c : input)
        udp[c] ++;

    //    vector<char> word({'1', '2', '3', '4'});
    //    vector<float> freq({0.05, 0.2, 0.5, 0.25});
    //    unordered_map<char, float> udp = construct(word, freq);

    cout << "词频统计:" << endl;
    for(auto iter = udp.begin(); iter != udp.end(); ++ iter)
        cout << iter->first << ": " << iter->second << endl;

    HuffmanTree *huff = new HuffmanTree();
    huff->genTree(udp);
    cout << huff->getAverageEnCodeLength(udp) << endl;
    cout << huff->getLeastEncoding(input) << endl;

    return 0;
}
