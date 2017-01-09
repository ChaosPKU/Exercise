/*
You want to build a house on an empty land which reaches all buildings in the shortest amount of distance. You can only move up, down, left and right. You are given a 2D grid of values 0, 1 or 2, where:

Each 0 marks an empty land which you can pass by freely.
Each 1 marks a building which you cannot pass through.
Each 2 marks an obstacle which you cannot pass through.
For example, given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2):

1 - 0 - 2 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0
The point (1,2) is an ideal empty land to build a house, as the total travel distance of 3+3+1=7 is minimal. So return 7.

Note:
There will be at least one building. If it is not possible to build such house according to the above rules, return -1.
*/

class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), res = 0, walk = 0, mindist = 0;
        int delta[] = {0, 1, 0, -1, 0};
        vector<vector<int>> total = grid;
        for(int i = 0;i < m; ++ i)
            for(int j = 0;j < n; ++ j){
                if(grid[i][j] == 1){   //从房子出发，计算到每个空地去的最短距离。
                    mindist = -1;
                    vector<vector<int>> dist = grid;
                    queue<pair<int, int>> Q;
                    Q.push(make_pair(i, j));
                    while(!Q.empty()){
                        int x = Q.front().first, y = Q.front().second;
                        Q.pop();
                        for(int d = 0;d < 4; ++ d){
                            int xx = x + delta[d], yy = y + delta[d + 1];
                            if(xx >= 0 && yy >= 0 && xx < m && yy < n && grid[xx][yy] == walk){ //walk保证不会走重，同时不会漏房子；
                                grid[xx][yy] --;
                                dist[xx][yy] = dist[x][y] + 1;
                                total[xx][yy] += dist[xx][yy] - 1;
                                Q.push(make_pair(xx, yy));
                                if (mindist < 0 || mindist > total[xx][yy])  // mindist表示所有空地到当前房子的距离中的最小值。
                                    mindist = total[xx][yy];
                            }
                        }
                    }
                    walk --;
                }
            }
        for(int i = 0;i < m; ++ i)
            for(int j = 0;j < n; ++ j)
                if(grid[i][j] < 0) grid[i][j] = 0;
        return mindist;
    }
};
