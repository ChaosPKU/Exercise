/*

Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:

nums = [
  [9,9,4],
  [6,6,8],
  [2,1,1]
]
Return 4
The longest increasing path is [1, 2, 6, 9].

Example 2:

nums = [
  [3,4,5],
  [3,2,6],
  [2,2,1]
]
Return 4
The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.

*/

class Solution {
private:
    int height = 0, width = 0;
    int walk(vector<vector<int>>& matrix, int i, int j, vector<vector<int>>& visited, int cur){
        if(i < 0 || j < 0 || i >= height || j >= width)
            return 0;
        if(matrix[i][j] <= cur)
            return 0;
        if(visited[i][j] > 0)
            return visited[i][j];
        int l = walk(matrix, i, j - 1, visited, matrix[i][j]);
        int r = walk(matrix, i, j + 1, visited, matrix[i][j]);
        int u = walk(matrix, i - 1, j, visited, matrix[i][j]);
        int d = walk(matrix, i + 1, j, visited, matrix[i][j]);
        visited[i][j] = max(l, max(r, max(u, d))) + 1;
        return visited[i][j];
    }
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        height = matrix.size();
        if(!height) return 0;
        width = matrix[0].size();
        if(!width) return 0;
        vector<vector<int>> visited(height, vector<int>(width, 0));
        int res = 0;
        for(int i = 0; i < height; ++ i){
            for(int j = 0; j < width; ++ j){
                res = max(walk(matrix, i, j, visited, INT_MIN), res);
            }
        }
        return res;
    }
};
