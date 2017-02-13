/*
输入

第1行：1个正整数，N。1≤N≤15

输出

第1行：1个长度为2^N的01串，每N位表示一个数字，不同的窗口表示的数字不同，恰好为0~2^N-1。
样例输入
3
样例输出
00010111
*/

// 构造一个图，共有2^(N-1)个顶点, 2^N条边, 表示数字0~2^(N-1)-1, 其中顶点i到j有边当且仅当i的后N-2个bits和j的N-2个bits相同, 则边i->j表示数字 (i << 1) & (j & 1), 可以证明不同的边表示的数字一定不同。
// 则对图求其欧拉回路即可。
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <set>
using namespace std;
int main(){
    int n, s;
    while(cin >> n){
        int N = 1 << (n - 2), cnt = 0;
        unordered_map<int, set<int>> udmp;
        for(int i = 0;i < N; ++ i){
            udmp[N | i].insert(i << 1);
            udmp[N | i].insert((i << 1) + 1);
            udmp[i].insert(i << 1);
            udmp[i].insert((i << 1) + 1);
        }
        stack<int> stk;
        stk.push(0);
        vector<int> res;
        while(!stk.empty()){
            s = stk.top();
            if(!udmp[s].empty()){
                stk.push(*(udmp[s].begin()));
                udmp[s].erase(udmp[s].begin());
            }
            else{
                res.push_back(stk.top());
                stk.pop();
            }
        }
        
        int num = res.back();
        for(int i = n - 2; i >= 0; -- i)
            cout << ((num >> i) & 1);
        for(int i = (int)res.size() - 2; i >= n - 1; -- i){
            cout << (res[i] & 1);
        }
    }
    return 0;
}
