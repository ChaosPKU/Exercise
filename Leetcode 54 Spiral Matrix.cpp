/*
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:

[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].
*/

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        int n = matrix.size();
        if(!n) return res;
        int m = matrix[0].size();
        int u = 0, d = n - 1, l = 0, r = m - 1;
        int dir_x[4] = {0,1,0,-1};
        int dir_y[4] = {1,0,-1,0};
        int x = 0, y = 0;
        while(u <= d || l <= r){
            bool flag[4] = {0};
            for(int i = 0;i < 4; ++ i){
                if(i > 1 && !flag[i-1]) break;
                while(true){
                    int xx = x + dir_x[i];
                    int yy = y + dir_y[i];
                    if(xx < u || xx > d || yy < l || yy > r)
                        break;
                    if(i == 3 && xx == u) break;
                    res.push_back(matrix[x][y]);
                    x = xx;
                    y = yy;
                    flag[i] = 1;
                }
            }
            ++ u; 
            ++ l;
            -- d;
            -- r;
        }
        res.push_back(matrix[x][y]);
    }
};
