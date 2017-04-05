/*
牛牛正在挑战一款名为01翻转的游戏。游戏初始有A个0,B个1，牛牛的目标就是把所有的值都变为1，每次操作牛牛可以任意选择恰好K个数字，并将这K个数字的值进行翻转(0变为1，1变为0)。牛牛如果使用最少的操作次数完成这个游戏就可以获得奖品，牛牛想知道最少的操作次数是多少？
例如:A = 4 B = 0 K = 3 
0000 -> 1110 -> 1001 -> 0100 -> 1111 
需要的最少操作次数为4 
输入描述:
输入为一行：
一共三个整数A(0 ≤ A ≤ 100,000),B(0 ≤ B ≤ 100,000),K(1 ≤ K ≤100,000).以空格分隔


输出描述:
输出一个整数，表示最少需要的操作次数。如果不能完成，则输出-1

输入例子:
4 0 3

输出例子:
4
*/

/*
链接：https://www.nowcoder.com/questionTerminal/9c4c9d10e3db4448b906c6e6cea22b7f
来源：牛客网
  设 n = A+B 
  设 位置值序列集合 E = {e1, e2, e3,...en}， ei ∈ {0, 1}，其中ei表示第i个位置上的值 （1 ≤ i ≤ n） 
  假设初始时，前面A个位置为0，后面B个位置为1 
  设 Ti 为 第i个位置上翻转的次数 
  因为一次翻转必翻转K个位置，假设进行了X次翻转（未知数），则有以下等式 
  ① XK = ∑Ti （1 ≤ i ≤ n） 
  因为同一个位置翻转2次得到是原来的值，所以为了使所有位置均为1， Ti 必满足以下条件： 
  ② Ti = 1 + 2Si （ei 初始为0） 
  ③ Ti = 2Si（ei 初始为1） 
  其中Si 表示第i个位置进行了 Si次2次翻转 
  结合①、②、③可得： 
  ④ XK = A + 2 ∑Si （1 ≤ i ≤ n） 
  ⑤ XK - A 必为偶数
  总的来看：在某些位置上进行了2次翻转，和A个位置的1次翻转，就全部为1了。 
  对 ∑Si 观察可得： 
  对于初始为1的位置，2次翻转次数不能超过X/2 
  对于初始为0的位置，2次翻转次数不能超过(X-1)/2 ，因为最后一次翻转不能属于“2次翻转”中的一次翻转 
  假设所有位置的2次翻转次数都达到最大，则有不等式： 
  ⑥ (XK - A)/2 = ∑Si （1 ≤ i ≤ n）≤ A ((X-1)/2) + B(X/2)
  满足⑤、⑥条件X即可满足题意 
  可以相信，X不能大于 A + B
*/

#include <iostream>
using namespace std;
int main(){
    int a, b, k, n, maxN;
    while(cin >> a >> b >> k){
        maxN = a + b;
        if(a == 0) 
            cout << 0 << endl;
        else {
            for(n = 0; n <= maxN; ++ n){
                if(n * k - a < 0 || (n * k - a) & 1)
                    continue;
                if((n * k - a) / 2 <= (n - 1) / 2 * a + n / 2 * b)
                    break;
            }
            if(n <= maxN) cout << n << endl;
            else cout << -1 << endl;
        }
    }
    return 0;
}

/*
链接：https://www.nowcoder.com/questionTerminal/9c4c9d10e3db4448b906c6e6cea22b7f
来源：牛客网
*/
#include <iostream>
using namespace std;
int solve(int a, int b, int k){
    if(a == 0) return 0;
    if(k == 0) return -1;
    if(a % k == 0) return a / k;
    if((a & 1) > (k & 1) || k >= a + b) return -1;
    int ret = a / k + 1;
    while(ret <= a + b){
        if(((ret * k - a) & 1) == 0 && ret * k <= ret * (a + b) - ((ret & 1) ? b : a))
            return ret;
        ++ ret;
    }
    return -1;
}
int main(){
    int a, b, k;
    while(cin >> a >> b >> k)
        cout << solve(a, b, k) << endl;
    return 0;
}


// DFS版本

#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;
int main(){
    int A, B, K, D, a, b, d, trans_a, trans_b, new_a, new_b, res;
    while(cin >> A >> B >> K){
        if(A == 0) res = 0;
        else {
            vector<int> mp(A + B + 1, -1);
            mp[A] = 0;
            queue<pair<int, int> > q;
            q.push(make_pair(A, 0));
            res = -1;
            for(D = 1; D <= A + B && !q.empty(); ++ D){
                auto p = q.front();
                q.pop();
                a = p.first, b = A + B - a, d = p.second;
                for(trans_a = max(K - b, 0); trans_a <= min(min(a, K), (a + K) / 2); ++ trans_a){
                    trans_b = K - trans_a;
                    new_a = a - trans_a + trans_b;
                    new_b = b - trans_b + trans_a;
                    if(new_a == 0){
                        res = d + 1;
                        break;
                    }
                    if(mp[new_a] == -1){
                        mp[new_a] = d + 1;
                        q.push(make_pair(new_a, d + 1));
                    }
                }
            }
        }
        cout << res << endl;
    }
    return 0;
}

