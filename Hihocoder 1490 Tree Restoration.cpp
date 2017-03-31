/*
https://hihocoder.com/problemset/problem/1490

There is a tree of N nodes which are numbered from 1 to N. Unfortunately, its edges are missing so we don't know how the nodes are connected. Instead we know:  

1. Which nodes are leaves  

2. The distance (number of edges) between any pair of leaves

3. The depth of every node (the root's depth is 1)

4. For the nodes on the same level, their order from left to right

Can you restore the tree's edges with these information? Note if node u is on the left of node v, u's parent should not be on the right of v's parent.

tree-restoration.png

输入
The first line contains three integers N, M and K. N is the number of nodes. M is the depth of the tree. K is the number of leaves.

The second line contains M integers A1, A2, ... AM. Ai represents the number of nodes of depth i.

Then M lines follow. The ith of the M lines contains Ai numbers which are the nodes of depth i from left to right.  

The (M+3)-th line contains K numbers L1, L2, ... LK, indicating the leaves.

Then a K × K matrix D follows. Dij represents the distance between Li and Lj.

1 ≤ N ≤ 100

输出
For every node from 1 to N output its parent. Output 0 for the root's parent.

样例输入
8 3 5  
1 3 4  
1  
2 3 4  
5 6 7 8  
3 5 6 7 8  
0 3 3 3 3  
3 0 2 4 4  
3 2 0 4 4  
3 4 4 0 2  
3 4 4 2 0
样例输出
0 1 1 1 2 2 4 4
*/

#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;
int main(){
    int N, M, K;
    int i, j;
    scanf("%d%d%d", &N, &M, &K);
    vector<int> prt(N + 1, 0), floor_size(M + 1, 0), leaves(K + 1);
    vector<bool> isLeaf(N + 1, 0);
    vector<vector<int> > nodes(M + 1), dist(N + 1, vector<int>(N + 1, 0));
    for(i = 1;i <= M; ++ i) {
        scanf("%d", &floor_size[i]);
        nodes[i].resize(floor_size[i]);
    }
    for(i = 1;i <= M; ++ i)
        for(int j = 0;j < floor_size[i]; ++ j)
            scanf("%d", &nodes[i][j]);
    for(i = 1;i <= K; ++ i){
        scanf("%d", &leaves[i]);
        isLeaf[leaves[i]] = 1;
    }
    for(i = 1;i <= K; ++ i)
        for(j = 1; j <= K; ++ j)
            scanf("%d", &dist[leaves[i]][leaves[j]]);
    for(i = M; i > 1; -- i){
        int uptr = 0, nptr = 0;
        while(uptr < nodes[i - 1].size() && nptr < nodes[i].size()){
            while(uptr < nodes[i - 1].size() && isLeaf[nodes[i - 1][uptr]]) uptr ++;
            if(uptr == nodes[i - 1].size()) break;
            prt[nodes[i][nptr]] = nodes[i - 1][uptr];
            while(++ nptr < nodes[i].size() && dist[nodes[i][nptr - 1]][nodes[i][nptr]] == 2)
                prt[nodes[i][nptr]] = prt[nodes[i][nptr - 1]];
            for(j = 1;j <= N; ++ j){
                dist[j][prt[nodes[i][nptr - 1]]] = dist[j][nodes[i][nptr - 1]] - 1;
                dist[prt[nodes[i][nptr - 1]]][j] = dist[nodes[i][nptr - 1]][j] - 1;
            }
            ++ uptr;
        }
    }
    for(i = 1;i <= N; ++ i)
        printf("%d ", prt[i]);
    printf("\n");
    return 0;
}
