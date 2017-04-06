/*

大家一定玩过“推箱子”这个经典的游戏。具体规则就是在一个N*M的地图上，有1个玩家、1个箱子、1个目的地以及若干障碍，其余是空地。玩家可以往上下左右4个方向移动，但是不能移动出地图或者移动到障碍里去。如果往这个方向移动推到了箱子，箱子也会按这个方向移动一格，当然，箱子也不能被推出地图或推到障碍里。当箱子被推到目的地以后，游戏目标达成。现在告诉你游戏开始是初始的地图布局，请你求出玩家最少需要移动多少步才能够将游戏目标达成。 
输入描述:
每个测试输入包含1个测试用例
第一行输入两个数字N，M表示地图的大小。其中0<N，M<=8。
接下来有N行，每行包含M个字符表示该行地图。其中 . 表示空地、X表示玩家、*表示箱子、#表示障碍、@表示目的地。
每个地图必定包含1个玩家、1个箱子、1个目的地。


输出描述:
输出一个数字表示玩家最少需要移动多少步才能将游戏目标达成。当无论如何达成不了的时候，输出-1。

输入例子:
4 4
....
..*@
....
.X..
6 6
...#..
......
#*##..
..##.#
..X...
.@#...

输出例子:
3
11

*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main(){
    int n, m;
    int dir[5] = {0, 1, 0, -1, 0};
    while(cin >> n >> m){
        char c;
        int px = 0, py = 0, bx = 0, by = 0, tx = 0, ty = 0, res = -1;
        vector<vector<int> > grid(n, vector<int>(m));
        vector<vector<bool> > visited(n * m, vector<bool>(n * m, 0));
        for(int i = 0;i < n; ++ i)
            for(int j = 0;j < m; ++ j){
                cin >> c;
                if(c == '.') grid[i][j] = 0; // 空地
                else if(c == '#') grid[i][j] = -1; // 障碍
                else if(c == 'X') { // 玩家
                    px = i; py = j;
                    grid[i][j] = -2;
                }
                else if(c == '*') { // 箱子
                    bx = i; by = j;
                    grid[i][j] = -3;
                }
                else if(c == '@') { // 目的地
                    tx = i; ty = j;
                    grid[i][j] = -4;
                }
            }
        if(bx == tx && by == ty) {
            cout << 0 << endl;
            continue;
        }
        visited[px * m + py][bx * m + by] = 1; // 状态 = 玩家位置+箱子位置
        queue<vector<int>> q;
        q.push(vector<int>({px, py, bx, by, 0}));
        while(res == -1 && !q.empty()){
            vector<int> vtr = q.front();
            q.pop();
            for(int i = 0;i < 4; ++ i){
                int pxx = vtr[0] + dir[i], pyy = vtr[1] + dir[i + 1], bxx = vtr[2], byy = vtr[3];
                if(pxx == bxx && pyy == byy){ // 人走到了箱子的位置，箱子也要随之移动
                    bxx = bxx + dir[i];
                    byy = byy + dir[i + 1];
                }
                if(pxx >= 0 && pyy >= 0 && pxx < n && pyy < m && grid[pxx][pyy] != -1 && bxx >= 0 && byy >= 0 && bxx < n && byy < m && grid[bxx][byy] != -1 && !visited[pxx * m + pyy][bxx * m + byy]){
//                    printf("%d %d %d %d %d -> %d %d %d %d %d\n", vtr[0], vtr[1], vtr[2], vtr[3], vtr[4], pxx, pyy, bxx, byy, vtr[4] + 1);
                    if(bxx == tx && byy == ty) {// 箱子抵达目的地
                        res = vtr[4] + 1;
                        break;
                    }
                    visited[pxx * m + pyy][bxx * m + byy] = 1;
                    q.push(vector<int>{pxx, pyy, bxx, byy, vtr[4] + 1});
                }
            }
        }
        cout << res << endl;
    }
    return 0;
}
