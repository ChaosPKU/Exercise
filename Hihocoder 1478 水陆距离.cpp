/*
时间限制:10000ms
单点时限:1000ms
内存限制:256MB
描述
给定一个N x M的01矩阵，其中1表示陆地，0表示水域。对于每一个位置，求出它距离最近的水域的距离是多少。  

矩阵中每个位置与它上下左右相邻的格子距离为1。

输入
第一行包含两个整数，N和M。

以下N行每行M个0或者1，代表地图。

数据保证至少有1块水域。

对于30%的数据，1 <= N, M <= 100  

对于100%的数据，1 <= N, M <= 800

输出
输出N行，每行M个空格分隔的整数。每个整数表示该位置距离最近的水域的距离。

样例输入
4 4  
0110  
1111  
1111  
0110
样例输出
0 1 1 0  
1 2 2 1  
1 2 2 1  
0 1 1 0
*/
#include <iostream>
#include <queue>
using namespace std;
int main(){
    int N, M;
    cin >> N >> M;
    char c;
    int dist[5] = {0, 1, 0, -1, 0};
    queue<pair<int, int>> Q;
    vector<vector<int> > grid(N, vector<int>(M, 2000));
    for(int i = 0;i < N; ++ i){
        getchar();
        for(int j = 0;j < M ; ++ j){
            cin >> c;
            if(c == '0') {
                grid[i][j] = c - '0';
                Q.push(make_pair(i, j));
            }
        }
    }
    while(!Q.empty()){
        int x = Q.front().first, y = Q.front().second;
        Q.pop();
        for(int i = 0;i < 4; ++ i){
            int xx = x + dist[i], yy = y + dist[i + 1];
            if(xx < 0 || yy < 0 || xx >= N || yy >= M) continue;
            if(grid[xx][yy] > grid[x][y] + 1){
                grid[xx][yy] = grid[x][y] + 1;
                Q.push(make_pair(xx, yy));
            }
        }
    }
    for(int i = 0;i < N; ++ i){
        for(int j = 0;j < M; ++ j)
            cout << grid[i][j] << " ";
        cout << endl;
    }
}
