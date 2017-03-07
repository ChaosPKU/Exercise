/*
Problem

"Look at the stars, look how they shine for you." - Coldplay, "Yellow"

In a galaxy far, far away, there are many stars. Each one is a sphere with a certain position (in three-dimensional space) and radius. It is possible for stars to overlap each other.

The stars are so incredibly beautiful to you that you want to capture them forever! You would like to build two cubes of the same integer edge length, and place them in space such that for each star, there is at least one cube that completely contains it. (It's not enough for a star to be completely contained by the union of the two cubes.) A star is completely contained by a cube if no point on the star is outside the cube; a point exactly on a cube face is still considered to be inside the cube.

The cubes can be placed anywhere in space, but they must be placed with their edges parallel to the coordinate axes. It is acceptable for the cubes to overlap stars or each other.

What is the minimum integer edge length that allows you to achieve this goal?

Input

The input starts with one line containing exactly one integer T, which is the number of test cases. T test cases follow.

Each test case begins with a line containing an integer, N, representing the number of stars.

This is followed by N lines. On the ith line, there are 4 space-separated integers, Xi, Yi, Zi and Ri, indicating the (X, Y, Z) coordinates of the center of the ith star, and the radius of the ith star.

Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the minimum cube edge length that solves the problem, as described above.

Limits

1 ≤ T ≤ 100.
-108 ≤ Xi ≤ 108, for all i.
-108 ≤ Yi ≤ 108, for all i.
-108 ≤ Zi ≤ 108, for all i.
1 ≤ Ri ≤ 108, for all i.
Small dataset

1 ≤ N ≤ 16.
Large dataset

1 ≤ N ≤ 2000.
Sample


Input 
 	
Output 
 
3
3
1 1 1 1
2 2 2 1
4 4 4 1
3
1 1 1 2
2 3 4 1
5 6 7 1
3
1 1 1 1
1 1 1 1
9 9 9 1

Case #1: 3
Case #2: 5
Case #3: 2
In the first test case, one solution is to place two cubes with an edge length of 3 such that their corners with minimum (x, y, z) coordinates are at (0, 0, 0) and (3, 3, 3).
In the second test case, one solution is to place two cubes with an edge length of 5 such that their corners with minimum (x, y, z) coordinates are at (-1, -1, -1) and (1, 2, 3).
*/

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int T, N;
int stars[2005][4], border[2][3], simulate[2][3], d[2];
int midres, res;

int main() {
    freopen("/Users/Apple/Downloads/C-small-practice.in.txt", "r", stdin);
    freopen("/Users/Apple/Downloads/C-large.out.txt", "w", stdout);
    
    scanf("%d", &T);
    for(int t = 1; t <= T; ++ t){
        scanf("%d", &N);
        res = 1000000000;
        for(int j = 0;j < 3; ++ j){
            border[0][j] = 1000000000;
            border[1][j] = -1000000000;
        }
        for(int i = 0; i < N; ++ i){
            scanf("%d%d%d%d", &stars[i][1], &stars[i][2], &stars[i][3], &stars[i][0]);
            for(int j = 0; j < 3; ++ j){
                border[0][j] = min(border[0][j], stars[i][j + 1] - stars[i][0]);
                border[1][j] = max(border[1][j], stars[i][j + 1] + stars[i][0]);
            }
        }
        // border保存完全覆盖大立方体的一对体对角顶点的坐标，simulate模拟全部八组体对角顶点(根据对称性，实际只需模拟四组)
        
        for(int x = 0; x < 1; ++ x){
            simulate[0][0] = border[x][0];
            simulate[1][0] = border[1 - x][0];
            for(int y = 0; y < 2; ++ y){
                simulate[0][1] = border[y][1];
                simulate[1][1] = border[1 - y][1];
                for(int z = 0; z < 2; ++ z){
                    simulate[0][2] = border[z][2];
                    simulate[1][2] = border[1 - z][2];
                    midres = 0;
                    for(int i = 0;i < N; ++ i){
                        d[0] = d[1] = 0;
                        for(int j = 0;j < 3; ++ j){
                            for(int k = 0;k < 2; ++ k){
                                d[k] = max(d[k], abs(stars[i][j + 1] - simulate[k][j]));
                            }
                        }
                        midres = max(midres, (min(d[0], d[1]) + stars[i][0]));
                    }
                    res = min(res, midres);
                }
            }
        }
        
        printf("Case #%d: %d\n",t, res);
        fprintf(stderr,"Case #%d: %d\n",t, res);
    }
    
    fclose(stdin);
    fclose(stdout);
    return 0;
}
