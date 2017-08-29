/*
Problem

You want to create a certain target string S, which consists only of lowercase English letters. You start with an empty string, and you are allowed to perform the following operations:

Add any single lowercase letter to the end of your string.
Copy any substring of your string (that is, all of the characters between some start point in your string and some end point in your string) to the clipboard. Doing this overwrites whatever was in the clipboard before. The clipboard starts off empty.
Add the entire contents of the clipboard to the end of your string. (The contents of the clipboard do not change.)
What is the smallest number of operations needed to create your target string? Note that you must create exactly the target string, with no additional letters.

Input

The first line of the input gives the number of test cases, T. T lines follow. Each line contains the target string S.

Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the minimum number of operations (as described in the problem statement) needed to create the target string.

Limits

S consists only of lowercase English letters in the range a through z.
Small dataset

1 ≤ T ≤ 100.
1 ≤ length of S ≤ 6.
Large dataset

1 ≤ T ≤ 100.
1 ≤ length of S ≤ 100.
Sample


Input 
 	
Output 
 
3
abcabab
aaaaaaaaaaa
vnsdmvnsnsdmkvdmkvnsdmk

Case #1: 6
Case #2: 7
Case #3: 15

The optimal solution for Sample Case #1 is:

Type a.
Type b.
Type c.
Copy ab to the clipboard.
Paste ab at the end of the string.
Paste ab at the end of the string.
The optimal solution for Sample Case #2 is:
Type a.
Type a.
Type a.
Copy aaa to the clipboard.
Paste aaa at the end of the string.
Copy aaaaa to the clipboard.
Paste aaaaa at the end of the string.
*/

// dp[i][j][l]表示以i为结尾，buffer是以j开始长度为l的子串
// op[i][j][l]表示以i和j开始，长度为l的子串是否相同，是预处理

#include <iostream>
#include <stdio.h>
#include <memory.h>
#include <string.h>
using namespace std;

const int maxN = 310;

int dp[maxN][maxN][maxN];
bool op[maxN][maxN][maxN];
char str[maxN];

inline void check_min(int &a, int b){
    (a > b) && (a = b);
}

int main(){
    freopen("/Users/Apple/Downloads/A-large-practice.in", "r", stdin);
    freopen("/Users/Apple/Downloads/A-large.out", "w", stdout);
    
    int T, t, i, j, l, n, c;
    scanf("%d", &T);
    for(t = 1; t <= T; ++ t){
        scanf("%s", str + 1);
        n = (int)strlen(str + 1);
        memset(dp, 127, sizeof(dp));
        
        dp[1][1][0] = 1;
        for(i = 1; i <= n; ++ i)
            for(j = 1; j <= n; ++ j)
                op[i][j][1] = str[i] == str[j];
        for(l = 2; l <= n; ++ l)
            for(i = 1; i + l - 1 <= n; ++ i)
                for(j = 1; j + l - 1 <= n; ++ j)
                    op[i][j][l] = op[i][j][l - 1] && str[i + l - 1] == str[j + l - 1];
        
        for(i = 1; i <= n; ++ i){
            c = 1e9;
            for(j = 1; j <= i; ++ j)
                for(l = 0; j + l - 1 <= i; ++ l)
                    c = min(dp[i][j][l], c);
            // 根据上一轮更新后的值，计算新的以i为结尾，buffer为任意子串所需最小步数
            
            if(i == n){
                printf("Case #%d: %d\n", t, c);
                break;
            }
            
            for(j = 1; j <= i; ++ j)
                for(l = 1; j + l - 1 <= i; ++ l)
                    dp[i][j][l] = min(dp[i][j][l], c + 1);
            // 表示copy as new buffer动作，此时buffer不能为空
            
            for(j = 1; j <= i; ++ j)
                for(l = 0; j + l - 1 <= i; ++ l){
                    if(op[i + 1][j][l])
                        check_min(dp[i + l][j][l], dp[i][j][l] + 1);
                    // 表示paste动作，能paste的前提是以i和j开始，长度为l的子串是必须相同
                    check_min(dp[i + 1][j][l], dp[i][j][l] + 1);
                    // 表示直接在末尾添加一个字符
                }
        }
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
