/*
描述
给定三个正整数 a、 b 和 p，满足 b 和 p 互质。这时分数 a / b 除以 p 的余数，即 a / b MOD p 可以定义为 a × b-1 MOD p。  

其中b-1 是 b 的逆元，它满足 1 ≤ b-1 < p 且 b × b-1 ≡ 1 MOD p，满足上述条件的 b-1有且仅有一个。  

例如 2-1 ≡ 4 MOD 7，因为2 × 4 ≡ 1 MOD 7； 3-1 ≡ 3 MOD 8，因为3 × 3 ≡ 1 MOD 8。  

于是我们可以利用b-1求出a / b MOD p，例如： 3 / 2 MOD 7 = 3 × 2-1 MOD 7 = 3 × 4 MOD 7 = 5

给定三个正整数 a、 b 和 p，满足 b 和 p 互质，求 a / b MOD p。  

输入
第一行包含3个正整数，a、b 和 p 满足 b 和 p 互质。  

对于30%的数据，1 ≤ a, b < p ≤ 100

对于80%的数据，1 ≤ a, b < p ≤ 100000  

对于100%的数据，1 ≤ a, b < p ≤ 1000001333

输出
输出 a / b MOD p的值。

样例输入
3 2 7
样例输出
5
*/
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

typedef long long LL;

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
    LL a, b, p;
    cin >> a >> b >> p;
    cout << a * (mod_reverse(b, p) % p) % p << endl;
    return 0;
}
