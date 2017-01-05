/*
A group of two or more people wants to meet and minimize the total travel distance. You are given a 2D grid of values 0 or 1, where each 1 marks the home of someone in the group. The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

For example, given three people living at (0,0), (0,4), and (2,2):

1 - 0 - 0 - 0 - 1
|   |   |   |   |
0 - 0 - 0 - 0 - 0
|   |   |   |   |
0 - 0 - 1 - 0 - 0
The point (0,2) is an ideal meeting point, as the total travel distance of 2+2+2=6 is minimal. So return 6.

Hint:

Try to solve it in one dimension first. How can this solution apply to the two dimension case?
*/

class Solution {
public:
    int minTotalDistance(vector<vector<int>>& grid) {
        vector<int> rows, cols;
        for(int i = 0;i < grid.size(); ++ i)
            for(int j = 0;j < grid[i].size(); ++ j)
                if(grid[i][j] == 1){
                    rows.push_back(i);
                    cols.push_back(j);
                }
        sort(rows.begin(), rows.end());
        sort(cols.begin(), cols.end());
        int i = 0, j = rows.size() - 1, res = 0;
        while(i < j) res += rows[j] - rows[i] + cols[j--] - cols[i++];
        return res;
    }
};
