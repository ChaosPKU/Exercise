/*
输入

第1行：2个正整数，N,M。分别表示骨牌上出现的最大数字和骨牌数量。1≤N≤1,000，1≤M≤5,000

第2..M+1行：每行2个整数，u,v。第i+1行表示第i块骨牌两端的数字(u,v)，1≤u,v≤N

输出

第1行：m+1个数字，表示骨牌首尾相连后的数字

比如骨牌连接的状态为(1,5)(5,3)(3,2)(2,4)(4,3)，则输出"1 5 3 2 4 3"

你可以输出任意一组合法的解。

样例输入
5 5
3 5
3 2
4 2
3 4
5 1
样例输出
1 5 3 4 2 3
*/

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <set>
using namespace std;
int main(){
    int n, m, s, t;
    while(cin >> n >> m){
        unordered_map<int, multiset<int>> udmp(n + 1);  // 可能有重复边
        vector<int> indegree(n + 1, 0);
        for(int i = 0;i < m; ++ i){
            cin >> s >> t;
            udmp[s].insert(t);
            udmp[t].insert(s);
            indegree[s] ++;
            indegree[t] ++;
        }
        int start = 1;
        for(int i = 1; i <= n; ++ i){
            if(indegree[i] & 1){
                start = i;
                break;
            }
        }
        stack<int> stk;
        stk.push(start);
        vector<int> res;
        while(!stk.empty()){
            s = stk.top();
            if(!udmp[s].empty()){
                stk.push(*(udmp[s].begin()));
                int b = *(udmp[s].begin());
                udmp[s].erase(udmp[s].begin());
                udmp[b].erase(udmp[b].find(s));  // 需要把反向边也删掉
            }
            else{
                res.push_back(stk.top());
                stk.pop();
            }
        }
        int i = (int)res.size() - 1;
        cout << res[i --];
        for(; i >= 0; -- i)
            cout << " " << res[i];
        cout << endl;
    }
    return 0;
}
