/*
Given an m x n matrix of positive integers representing the height of each unit cell in a 2D elevation map, compute the volume of water it is able to trap after raining.

Note:
Both m and n are less than 110. The height of each unit cell is greater than 0 and is less than 20,000.

Example:

Given the following 3x6 height map:
[
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]

Return 4.

The above image represents the elevation map [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]] before the rain.


After the rain, water are trapped between the blocks. The total volume of water trapped is 4.
*/

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        if(heightMap.empty()) return 0;
        int n = heightMap.size(), m = heightMap[0].size(), res = 0, mx = -1;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
        vector<vector<bool>> visited(n, vector<bool>(m, 0));
        int dir[5] = {0, 1, 0, -1, 0};
        for(int i = 0;i < m; ++ i){
            q.push(make_pair(heightMap[0][i], i));
            q.push(make_pair(heightMap[n - 1][i], (n - 1) * m + i));
            visited[0][i] = visited[n - 1][i] = 1;
        }
        for(int i = 1;i < n - 1; ++ i){
            q.push(make_pair(heightMap[i][0], i * m));
            q.push(make_pair(heightMap[i][m - 1], i * m + m - 1));
            visited[i][0] = visited[i][m - 1] = 1;
        }
        while(!q.empty()){
            pair<int, int> t = q.top();
            q.pop();
            int h = t.first, r = t.second / m, c = t.second % m;
            mx = max(mx, h);
            for(int i = 0;i < 4; ++ i){
                int x = r + dir[i], y = c + dir[i + 1];
                if(x >= 0 && y >= 0 && x < n && y < m && !visited[x][y]){
                    visited[x][y] = 1;
                    if(heightMap[x][y] < mx) res += mx - heightMap[x][y];
                    q.push(make_pair(heightMap[x][y], x * m + y));
                }
            }
        }
        return res;
    }
};
