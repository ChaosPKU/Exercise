/*
描述
小Hi在北方的暖气里温暖如春，小Ho却在南方的艳阳里感受大雪纷飞。距离使得他们连一起打麻将的机会都没有，失落的小Hi一个人玩起了麻将。

小Hi玩的是四川麻将，因此只有3种序数牌万、筒、条，每种花色一到九各4张。

小Hi起手拥有14张牌，之后小Hi每摸一张牌后，如果没有胡牌，就出一张牌，直至胡牌或牌被摸光。反正一个人玩又赢不到小Ho的钱，因此小Hi永远也不会选择暗杠。

胡牌的规则如下：

手中14张牌最多只能属于两个花色。

手中14张牌的牌型须满足下列两个条件之一：

1）3 + 3 + 3 + 3 + 2，其中的3代表一坎（指同花色且同数字、或同花色且数字相连的三张牌），其中的2代表一个对子（指两张同花色且同数字的牌）。

2）2 × 7，即14张牌构成7个对子，特别的，四张花色数字全相同的牌可以看作两个对子。
万、筒、条分别记为a, b, c，以下对能胡牌的牌型举出一些例子：

a1 a2 a3 a5 a5 a5 c3 c4 c5 c5 c6 c7 c7 c7

b2 b2 b5 b5 b7 b7 b8 b8 c1 c1 c2 c2 c3 c3

现给出小Hi的起手牌，并按顺序给出场上其余小Hi将要摸的牌。（小Hi只拿出了一副麻将的一部分牌玩，因此并不是每张牌都会被摸到。）

请计算小Hi最早在摸第几张牌之后就可能胡牌，天胡（起手牌构成胡牌牌型）记为第0张。无法胡牌输出-1。

输入
每张牌用a, b或c其后紧接一个数字1-9表示。

第一行是一个正整数n (n <= 94)，代表将要摸的牌。

第二行是14张手牌。

第三行是n张底牌，按摸牌顺序给出。

输出
输出一个整数，代表最早在摸第几张牌之后可能胡牌，无法胡牌输出-1。

样例输入
12
a1 a1 a1 a2 a3 a4 a5 a6 a7 a8 a9 a9 a9 c1
c2 b1 b2 b4 b5 c1 b7 b8 a1 a2 a3 a4
样例输出
6
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int num[108], col[108];
int colors[4] = {0, 1, 2, 0};

/*
int DP(int tmp[]){
    int dp[10][6][6] = {0};  // 前i位,从第i位刨去j个, 从第i-1位刨去k个, 最大
    int i, j, k, t;
    
    memset(dp, 1 << 7, sizeof(dp));
    dp[0][0][0] = 0;
    
    for(i = 1; i <= 2; ++ i)
        for(j = tmp[i];j >= 0; -- j)
            for(k = tmp[i - 1];k >= 0; -- k)
                dp[i][j][k] = max(dp[i - 1][k][0] + (tmp[i] - j) / 3, 0);
    
    for(i = 3;i < 10; ++ i)
        for(j = tmp[i];j >= 0; -- j)
            for(k = tmp[i - 1];k >= 0; -- k){
                dp[i][j][k] = max(dp[i][j + 1][k], dp[i][j][k + 1]);
                dp[i][j][k] = max(0, dp[i][j][k]);
                for(t = 1; t <= min(min(tmp[i - 1] - k, tmp[i - 2]), tmp[i] - j); ++ t)  // t 可以跟前两位组的链子数目
                    dp[i][j][k] = max(dp[i][j][k], max(dp[i - 1][k + t][t], dp[i - 2][t][0]) + t + (tmp[i] - j - t >= 3));
                dp[i][j][k] = max(dp[i][j][k], dp[i - 1][k][0] + (tmp[i] - j >= 3)); // 不跟前面组链子
            }
    
    return dp[9][0][0];
}
*/

void DFS(int tmp[], int &res, int counter, int begin){
    if(begin >= 10){
        res = max(res, counter);
        return ;
    }
    if(tmp[begin] >= 3){
        tmp[begin] -= 3;
        DFS(tmp, res, counter + 1, begin);
        tmp[begin] += 3;
    }
    if(begin <= 7 && tmp[begin] >= 1 && tmp[begin + 1] >= 1 && tmp[begin + 2] >= 1){
        tmp[begin] -= 1;
        tmp[begin + 1] -= 1;
        tmp[begin + 2] -= 1;
        DFS(tmp, res, counter + 1, begin);
        tmp[begin] += 1;
        tmp[begin + 1] += 1;
        tmp[begin + 2] += 1;
    }
    DFS(tmp, res, counter, begin + 1);
}

int solve(int tmp[], int flag){
    int res = 0;
    if(flag){
        res = -10000;
        for(int i = 1;i < 10; ++ i)
            if(tmp[i] >= 2){
                tmp[i] -= 2;
                res = max(res, solve(tmp, 0));
                tmp[i] += 2;
            }
    }
    else DFS(tmp, res, 0, 0);
    return res;
}

bool check(int x){
    int tmp[3][10] = {0};
    for(int i = 0;i <= x; ++ i)
        tmp[col[i]][num[i]] ++;
    
    int pr[3] = {0};
    for(int i = 0;i < 3; ++ i)
        for(int k = 1; k < 10; ++ k)
            if(tmp[i][k] >= 2) pr[i] += tmp[i][k] / 2;
    for(int i = 0;i < 3; ++ i)
        if(pr[colors[i]] + pr[colors[i + 1]] >= 7)
            return true;
    
    int pl[3][2] = {0}; // 0代表提供一对,1代表不提供一对;
    for(int i = 0;i < 3; ++ i)
        for(int j = 0;j < 2; ++ j)
            pl[i][j] = solve(tmp[i], j);
    for(int i = 0;i < 3; ++ i)
        for(int j = 0;j < 2; ++ j)
            if(pl[colors[i]][j] + pl[colors[i + 1]][1 - j] >= 4)
                return true;
    
    return false;
}

int main(){
    int n, t;
    char c;
    
    cin >> n;
    cin.get();
    
    for(int i = 0; i < 14; ++ i){
        cin >> c >> t;
        cin.get();
        num[i] = t;
        col[i] = c - 'a';
    }
    
    for(int i = 14; i < n + 14; ++ i){
        cin >> c >> t;
        cin.get();
        num[i] = t;
        col[i] = c - 'a';
    }
    
    int b = 13, e = n + 14;
    while(b < e){
        int m = (b + e) >> 1;
        if(check(m)) e = m;
        else b = m + 1;
    }
    
    if(e == n + 14) cout << -1 << endl;
    else cout << e - 13 << endl;
//    int tmp[10] = {0, 3, 1, 1, 2, 4, 1, 0, 1, 0};
//    int tmp[10] = {0, 1, 1, 2, 1, 2, 0, 0, 1, 0};
//    cout << solve(tmp, 0) << endl;
    return 0;
}
