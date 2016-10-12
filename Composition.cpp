/*
 Composition
 Alice writes an English composition with a length of N characters. However, her teacher requires that M illegal pairs of characters cannot be adjacent, and if 'ab' cannot be adjacent, 'ba' cannot be adjacent either.
 In order to meet the requirements, Alice needs to delete some characters.
 Please work out the minimum number of characters that need to be deleted.
 输入
 The first line contains the length of the composition N.
 The second line contains N characters, which make up the composition. Each character belongs to 'a'..'z'.
 The third line contains the number of illegal pairs M.
 Each of the next M lines contains two characters ch1 and ch2,which cannot be adjacent.
 For 20% of the data: 1 ≤ N ≤ 10
 For 50% of the data: 1 ≤ N ≤ 1000
 For 100% of the data: 1 ≤ N ≤ 100000, M ≤ 200.
 输出
 One line with an integer indicating the minimum number of characters that need to be deleted.
 样例输入
 5
 abcde
 3
 ac
 ab
 de
 样例输出
 2
 */
#include <bits/stdc++.h>
using namespace std;
int cf[26][26];
int N, M;
int dp[26];
char str[100005];
int main(){
    memset(cf, 0, sizeof(int));
    memset(dp, 0, sizeof(int));
    scanf("%d\n", &N);
    for(int i = 0;i < N; ++ i)
        scanf("%c", &str[i]);
    scanf("%d", &M);
    char a,b;
    for(int i = 0;i < M; ++ i){
        getchar();
        scanf("%c%c", &a, &b);
        cf[a - 'a'][b - 'a'] = 1;
        cf[b - 'a'][a - 'a'] = 1;
    }
    for(int i = 0;i < N; ++ i){
        int idx = str[i] - 'a';
        if(!cf[idx][idx]) dp[idx] ++;
        for(int j = 0;j < 26; ++ j){
            if(idx != j && !cf[idx][j]){
                dp[idx] = max(dp[j] + 1, dp[idx]);
            }
        }
    }
    int maxN = 0;
    for(int i = 0;i < 26; ++ i)
        maxN = max(maxN, dp[i]);
    printf("%d\n", N - maxN);
    return 0;
}
