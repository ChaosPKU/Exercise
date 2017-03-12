/*
 描述
 小Hi在玩一个游戏,他需要把1, 2, 3, ... NM填入一个N行M列的矩阵中,使得矩阵每一行从左到右、每一列从上到下都是递增的。
 
 例如如下是3x3的一种填法：
 
 136
 247
 589
 给定N和M,小Hi希望知道一共有多少种不同的填法。
 
 输入
 一行包含两个整数N和M。
 
 对于60%的数据 1 <= N <= 2, 1 <= M <= 100000
 
 对于20%的数据 N = 3, 1 <= M <= 100
 
 对于100%的数据 1 <= N <= 3, 1 <= M <= 100000
 
 输出
 输出一共有多少种不同的填法。由于结果可能很大,你只需输出答案模109+7的余数。
 
 样例输入
 3 2
 样例输出
 5
 */

/*
 N = 2时, 问题等价为在一个格点阵列中,从（0,0）点走到（n,m）点且不穿过对角线x == y的方法数（可以走到x == y的点）
 上述问题等价为在一个格点阵列中,从（0,0）点走到（n + 1,m）点且不经过对角线x == y的方法数（x > y）
 第一步走到（0,1）,这样从（0,1）走到（n + 1,m）无论如何也要经过x == y的点,这样的方法数为C(n+m,m-1);
 第一步走到（1,0）,又有两种可能
    不经过x == y的点,即所要求的情况
    经过x == y的点,可通过对称性得到,同第一步走到（0,1）的情况一样,方法数为C(n+m,m-1)
 所以问题的解为C(n+m+1,m) - 2*C(n+m,m-1) = C(n+m,m) - C(n+m,m-1)
 题目中n = m = M,所以二维题解即为2dCatalan(M)
 N = 3时,可以推广到三维格点阵列,题解可以类似推理得到。
 */


#include <iostream>
#include <vector>
using namespace std;

typedef long long LL;
const int mod = 1e9 + 7;

inline LL fractorial(LL x, LL y){
    LL res = x;
    for(LL i = x + 1;i <= y; ++ i)
        res = res * i % mod;
    return res;
}

inline LL extend_gcd(LL a,LL b,LL &x,LL &y)
{
    if(a == 0 && b == 0)
        return -1ll;
    if(b == 0)
    {
        x = 1ll;
        y = 0ll;
        return a;
    }
    LL d = extend_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

inline LL mod_reverse(LL a,LL n)
{
    LL x, y, d = extend_gcd(a, n, x, y);
    if(d == 1)
        return (x % n + n) % n;
    else
        return -1ll;
}

int main(){
    int N, M;
    cin >> N >> M;
    if(N == 1) cout << 1 << endl;
    else if(N == 2){
        //2d Catalan numbers; a(n) = (2*n)!/(n!*(n+1)!);
        LL num1 = fractorial(1, M), num2 = num1 * (M + 1) % mod, num3 = num1 * fractorial(M + 1, 2 * M) % mod;
        cout << num3 * mod_reverse(num1 * num2 % mod, mod) % mod << endl;
    }
    else if(N == 3){
        //3d Catalan numbers; a(n) = 2*(3*n)!/(n!*(n+1)!*(n+2)!);
        LL num1 = fractorial(1, M), num2 = num1 * (M + 1) % mod, num3 = num2 * (M + 2) % mod, num4 = num1 * fractorial(M + 1, 3 * M) % mod;
        cout << 2 * num4 * mod_reverse((num1 * num2 % mod) * num3 % mod, mod) % mod << endl;
    }
    return 0;
}
