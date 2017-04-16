/*
描述
某人有N袋金币，其中第i袋内金币的数量是Ai。现在他决定选出2袋金币送给小Hi，再选2袋金币送给小Ho，同时使得小Hi和小Ho得到的金币总数相等。他想知道一共有多少种不同的选择方法。

具体来说，有多少种下标四元组(i, j, p, q)满足i, j, p, q两两不同，并且i < j, p < q, Ai + Aj = Ap + Aq。  

例如对于数组A=[1, 1, 2, 2, 2]，一共有12种选法：

i j p q
1 3 2 4
1 3 2 5
1 4 2 3
1 4 2 5
1 5 2 3
1 5 2 4
2 3 1 4
2 3 1 5
2 4 1 3
2 4 1 5
2 5 1 3
2 5 1 4
输入
第一行包含一个整数N。  

第二行包含N个整数，A1, A2, A3 ... AN。

对于70%的数据，1 <= N <= 100  

对于100%的数据，1 <= N <= 1000, 1 <= Ai <= 1000000

输出
不同选择的数目。

样例输入
5  
1 1 2 2 2
样例输出
12
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main(){
    int n;
    long long res = 0;
    cin >> n;
    vector<int> vtr(n);
    for(int i = 0;i < n; ++ i)
        cin >> vtr[i];
    unordered_map<int, int> udmp, mp;
    for(int i = 0;i < n; ++ i){ // 枚举四个点中的最大值
        for(int j = 0;j < i; ++ j){  // 枚举与最大值配对的点
            res += (long long)udmp[vtr[i] + vtr[j]] - mp[vtr[i]]; // 在i之前所有能够配对和vtr[i] + vtr[j]的点对中刨去有j的点，个数就是i之前与其值相同的点的个数
            if(vtr[i] == vtr[j]) res ++; // 如果i,j值相同，则在上式减的时候会多减一个i
        }
        for(int j = 0;j < i; ++ j)
            udmp[vtr[i] + vtr[j]] ++;
        mp[vtr[i]] ++;
    }
    cout << 2 * res << endl;
    return 0;
}
