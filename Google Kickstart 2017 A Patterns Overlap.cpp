/*
Problem

Alice likes reading and buys a lot of books. She stores her books in two boxes; each box is labeled with a pattern that matches the titles of all of the books stored in that box. A pattern consists of only uppercase/lowercase English alphabet letters and stars (*). A star can match between zero and four letters. For example, books with the titles GoneGirl and GoneTomorrow can be put in a box with the pattern Gone**, but books with the titles TheGoneGirl, and GoneWithTheWind cannot.

Alice is wondering whether there is any book that could be stored in either of the boxes. That is, she wonders if there is a title that matches both boxes' patterns.

Input

The first line of the input gives the number of test cases, T. T test cases follow. Each consists of two lines; each line has one string in which each character is either an uppercase/lowercase English letter or *.

Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is TRUE if there is a string that matches both patterns, or FALSE if not.

Limits

1 ≤ T ≤ 50.
Small dataset

1 ≤ the length of each pattern ≤ 200.
Each pattern contains at most 5 stars.
Large dataset

1 ≤ the length of each pattern ≤ 2000.
Sample


Input 
 	
Output 
 
3
****
It
Shakes*e
S*speare
Shakes*e
*peare

Case #1: TRUE
Case #2: TRUE
Case #3: FALSE


In sample case #1, the title It matches both patterns. Note that it is possible for a * to match zero characters.

In sample case #2, the title Shakespeare matches both patterns.

In sample case #3, there is no title that matches both patterns. Shakespeare, for example, does not work because the * at the start of the *peare pattern cannot match six letters.
*/
#include <cstdio>
#include <cstring>
using namespace std;

int T;
int S[2][10005];
int Len[2];
char Tmp[2005];
bool DP[10005][10005];

int main() {
    freopen("/Users/Apple/Downloads/B-large-practice.in.txt", "r", stdin);
    freopen("/Users/Apple/Downloads/C-large.out.txt", "w", stdout);
    
    scanf("%d", &T);
    for(int t = 1;t <= T; ++ t){
        for(int i = 0;i < 2; ++ i){
            scanf("%s", Tmp);
            Len[i] = 0;
            for(int j = 0;Tmp[j] != 0; ++ j){
                if(Tmp[j] == '*')
                    for(int k = 0;k < 4; ++ k)
                        S[i][++ Len[i]] = '*';
                else S[i][++ Len[i]] = Tmp[j];
            }
        }
        memset(DP, 0, sizeof(DP));
        DP[0][0] = 1;
        for(int i = 1;i <= Len[0]; ++ i)
            if(S[0][i] == '*') DP[i][0] = 1;
            else break;
        for(int i = 1;i <= Len[1]; ++ i)
            if(S[1][i] == '*') DP[0][i] = 1;
            else break;
        for(int i = 1;i <= Len[0]; ++ i)
            for(int j = 1;j <= Len[1]; ++ j){
                if(S[0][i] == S[1][j] || S[0][i] == '*' || S[1][j] == '*')
                    DP[i][j] |= DP[i - 1][j - 1];
                if(S[0][i] == '*') DP[i][j] |= DP[i - 1][j];
                if(S[1][j] == '*') DP[i][j] |= DP[i][j - 1];
            }
        if (DP[Len[0]][Len[1]]) {
            printf("Case #%d: TRUE\n",t);
//            fprintf(stderr,"Case #%d: TRUE\n",t);
        } else {
            printf("Case #%d: FALSE\n",t);
//            fprintf(stderr,"Case #%d: FALSE\n",t);
        }
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
