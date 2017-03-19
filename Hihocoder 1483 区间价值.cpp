/*
 1483 : 区间价值
 时间限制:10000ms
 单点时限:1000ms
 内存限制:256MB
 描述
 给定n个数A1...An，小Ho想了解AL..AR中有多少对元素值相同。小Ho把这个数目定义为区间[L,R]的价值，用v[L,R]表示。
 
 例如1 1 1 2 2这五个数所组成的区间的价值为4。
 
 现在小Ho想知道在所有的的v[L,R](1 <= L <= R <= n)中，第k小的值是多少。
 
 输入
 第一行一个数T(T<=10)，表示数据组数。
 
 对于每一组数据：
 
 第一行两个数n，k（1<=n<=200,000,1<=k<=n*(n+1)/2）
 
 第二行n个数A1…An(1<=Ai<=1,000,000,000)
 
 输出
 一个数表示答案。
 
 样例输入
 2
 4 7
 1 1 2 3
 3 6
 100 100 100
 样例输出
 0
 3
 */
 
 //二分答案O(n)验证
 //一个很好的性质就是 V[L, R] >= V[L + 1, R] && V[L, R] >= V[L, R - 1];
 
#include <stdio.h>
#include <unordered_map>
using namespace std;
typedef long long LL;
int num[200005], tmp[200005];
int T, N, tot;
LL K;
unordered_map<int, int> udmp;
// O(n)时间内检查区间价值小于m的个数是否小于K
bool check(LL m){
    int b = 0, e = 0;
    LL cnt = 0, cur = 0;  //cur表示当前窗口b,e内部所有的区间价值和
    for(int i = 1;i <= tot; ++ i) tmp[i] = 0;
    for(; e < N; ++ e){
        cur += tmp[num[e]] ++;  //当前e节点的加入带来了多少额外的区间价值
        while(cur > m) cur -= -- tmp[num[b ++]];  //区间价值大于m时，需要减小窗口
        cnt += e - b + 1;  //以当前e节点为右端点且区间价值小于m的区间个数
    }
    return cnt < K;
}
int main(){
    scanf("%d", &T);
    while(T --){
        scanf("%d%lld", &N, &K);
        tot = 0;
        udmp.clear();
        for(int i = 0;i < N; ++ i){
            scanf("%d", &num[i]);
            if(udmp.find(num[i]) == udmp.end()) udmp[num[i]] = ++ tot;
            num[i] = udmp[num[i]];  //数少范围大,压缩以节省空间
        }
        LL b = 0, e = (LL)N * (N - 1) / 2;
        while(b <= e){
            LL m = (e + b) >> 1;
            if(check(m)) b = m + 1;
            else e = m - 1;
        }
        printf("%lld\n", b);
    }
    return 0;
}
