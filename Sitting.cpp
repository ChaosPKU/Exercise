/*
 Problem

The Codejamon game is on fire! Many players have gathered in an auditorium to fight for the World Championship. At the opening ceremony, players will sit in a grid of seats with R rows and C columns.

The competition will be intense, and the players are sensitive about sitting near too many of their future opponents! A player will feel too crowded if another player is seated directly to their left and another player is seated directly to their right. Also, a player will feel too crowded if one player is seated directly in front of them and another player is seated directly behind them.

What is the maximum number of players that can be seated such that no player feels too crowded?
Input

The first line of the input gives the number of test cases, T. T test cases follow. Each test case consists of one line with two integers R and C: the number of rows and columns of chairs in the auditorium.

Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the maximum number of players that can be seated, as described in the problem statement.

Limits

1 ≤ T ≤ 100.
Small dataset

1 ≤ R ≤ 5.
1 ≤ C ≤ 5.
Large dataset

1 ≤ R ≤ 100.
1 ≤ C ≤ 100.
Sample


Input

Output

3
2 2
2 3
4 1
Case #1: 4
Case #2: 4
Case #3: 3
In sample case #1, we can fill all seats, and no player will feel too crowded.

In sample case #2, each row has three seats. We can't put three players in a row, since that would make the middle player feel too crowded. One optimal solution is to fill each of the first two columns, for a total of four players.

In sample case #3, one optimal solution is to fill the first two rows and the last row, for a total of three players.
 */
#include "MyHeader.h"
int main() {
    freopen("/Users/Apple/Downloads/B-large-practice.in.txt", "r", stdin);
    freopen("/Users/Apple/Downloads/B-large-practice.out.txt", "w", stdout);
    int tot = 0;
    int R = 0, C = 0;
    scanf("%d", &tot);
    for(int i = 1;i <= tot; ++ i){
        scanf("%d%d", &R, &C);
        int c = 2 * (C / 3) + C % 3;
        int r1 = R / 3 + (R % 3 >= 1);
        int r2 = R / 3 + (R % 3 >= 2);
        int res = 0;
        if(R <= 2) res = R * c;
        else if(C <= 2) res = C * (r1 + r2);
        else if(C % 3 == 0) res = R * c;
        else if(C % 3 == 1) res = R * c - (R - r1 - r2);
        else res = R * c - (R - r1);
        printf("Case #%d: %d\n", i, res);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}
