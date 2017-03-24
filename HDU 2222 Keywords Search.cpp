/*
Problem Description
In the modern time, Search engine came into the life of everybody like Google, Baidu, etc.
Wiskey also wants to bring this feature to his image retrieval system.
Every image have a long description, when users type some keywords to find the image, the system will match the keywords with description of image and show the image which the most keywords be matched.
To simplify the problem, giving you a description of image, and some keywords, you should tell me how many keywords will be match.
 

Input
First line will contain one integer means how many cases will follow by.
Each case will contain two integers N means the number of keywords and N keywords follow. (N <= 10000)
Each keyword will only contains characters 'a'-'z', and the length will be not longer than 50.
The last line is the description, and the length will be not longer than 1000000.
 

Output
Print how many keywords are contained in the description.
 

Sample Input
1
5
she
he
say
shr
her
yasherhs
 

Sample Output
3
*/
#include <iostream>
#include <memory.h>
#include <string.h>
using namespace std;

#define node_size 500001   //节点个数
#define vocab_size 26       //字符集大小

class TrieNode{
public:
    int counter, flag;  // counter 计数器 flag 状态域
    TrieNode *fail, *children[vocab_size];
    TrieNode():fail(NULL),counter(0){
        memset(children, NULL, sizeof(children));
    }
};
TrieNode dict[node_size + 1];   //存储字典库结点
TrieNode *Q[node_size + 1];     //模拟队列，用于BFS构造失败指针
int ord[256];   // vocabulary => index

class AC_DFA{
private:
    int size;
    TrieNode *root;
public:
    AC_DFA(){
        transID();
        init();
    }
    void init(){
        memset(dict, 0, sizeof(dict));
        root = NULL;
        size = 0;
        root = newNode();
    }
    void transID(){  // 构建映射，可根据实际情况修改
        for(int i = 0;i < vocab_size; ++ i)
            ord['a' + i] = i;
    }
    TrieNode* newNode(){
        dict[size].flag = size;
        dict[size].fail = root;
        return &dict[size ++];
    }
    void insert(char* word, int l){
        TrieNode *cur = root;
        for(int i = 0;i < l; ++ i){
            if(!cur->children[ord[word[i]]])
                cur->children[ord[word[i]]] = newNode();
            cur = cur->children[ord[word[i]]];
        }
        cur->counter ++;    //用于统计字典库重复字符
    }
    void setfail(){
        Q[0] = root;
        root->fail = NULL;
        for(int move = 0, save = 1; move < save; ++ move){  //模拟队列
            TrieNode *cur = Q[move];
            for(int i = 0;i < vocab_size; ++ i){
                if(cur->children[i]){
                    TrieNode *ptr = cur->fail;
                    while(ptr && !ptr->children[i]) ptr = ptr->fail;
                    cur->children[i]->fail = ptr ? ptr->children[i] : root;
                    //cur->children[i]->counter += cur->children[i]->fail->counter; //状态合并，不能计数
                    Q[save ++] = cur->children[i];
                }
                else cur->children[i] = cur == root ? root : cur->fail->children[i];
            }
        }
    }
    int query(char* line, int L){   //统计字串line中单词出现个数，可重复及交叉
        int res = 0;
        TrieNode *tmp, *cur = root;
        for(int i = 0;i < L; ++ i){
            cur = cur->children[ord[line[i]]];
            tmp = cur;
            while(tmp && tmp->counter){
                res += tmp->counter;
                tmp->counter = 0;      //用于统计时相同的单词只计数一次，若可重复则注释掉
                tmp = tmp->fail;
            }
        }
        return res;
    }
};

int main(){
    int N, T;
    char str[1000001];
    scanf("%d", &T);
    while(T --){
        scanf("%d", &N);
        AC_DFA *obj = new AC_DFA();
        while(N --){
            scanf("%s", str);
            obj->insert(str, (int)strlen(str));
        }
        obj->setfail();
        scanf("%s", str);
        printf("%d\n", obj->query(str, (int)strlen(str)));
    }
    return 0;
}
