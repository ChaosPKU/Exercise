/*
描述
小Hi在游乐园中获得了M张奖券，这些奖券可以用来兑换奖品。

可供兑换的奖品一共有N件。第i件奖品需要Wi张奖券才能兑换到，其价值是Pi。  

小Hi使用不超过M张奖券所能兑换到的最大奖品总价值是多少？

输入
第一行两个整数N，M。  

接下来N行，每行两个整数Wi，Pi。  

对于 50%的数据： 1≤N,M≤1000  

对于 100%的数据： 1≤N,M≤105,1≤Pi,Wi≤10。  

输出
一行一个整数，表示最大的价值。

样例输入
3 10  
2 3  
8 8   
10 10
样例输出
11 
*/

//多重背包二进制优化
#include <iostream>
#include <unordered_map>

using namespace std;
const int mod = 100;

int main(){
    int N, M;
    int i, j, w, p;
    cin >> N >> M;
    unordered_map<int, int> udmp;
    vector<int> W, P;
    vector<int> DP(M + 1, 0);
    
    for(i = 0;i < N; ++ i){
        cin >> w >> p;
        udmp[w * mod + p] ++;
    }
    
    for(auto e : udmp){
        w = e.first / mod, p = e.first % mod;
        for(i = 1;2 * i - 1 <= e.second; i <<= 1){
            W.push_back(i * w);
            P.push_back(i * p);
        }
        i -= 1;
        if(i < e.second){
            W.push_back(w * (e.second - i));
            P.push_back(p * (e.second - i));
        }
    }
    
    for(i = 0;i < W.size(); ++ i)
        for(j = M; j >= W[i]; -- j)
            DP[j] = max(DP[j], DP[j - W[i]] + P[i]);
    cout << DP[M] << endl;
    return 0;
}
