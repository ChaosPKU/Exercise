/*
There are a row of n houses, each house can be painted with one of the k colors. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by a n x k cost matrix. For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of painting house 1 with color 2, and so on... Find the minimum cost to paint all houses.

Note:
All costs are positive integers.
*/

//dp[i][j]表示将第i个post涂成j颜色之后带来的最小开销，则dp[i][j] = min{dp[i - 1][x], x = 1 ~ k 且 x != j} + cost[i][j];
//时间复杂度是O(nk)，空间复杂度，由于i只跟i-1有关系，可以优化为O(k)，而如果事先计算好上一层的最小值和次小值，可以继续优化至O(1)。

class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        int n = costs.size();
        if(n == 0) return 0;
        int k = costs[0].size(), min1 = 0, min2 = 0, index = 0;
        for(int i = 0;i < n; ++ i){
            int m1 = INT_MAX, m2 = INT_MAX, idx = 0, c = 0;
            for(int j = 0;j < k; ++ j){
                if(j == index) c = min2 + costs[i][j];
                else c = min1 + costs[i][j];
                if(c < m1){
                    m2 = m1;
                    m1 = c;
                    idx = j;
                }
                else if(c < m2)
                    m2 = c;
            }
            min1 = m1, min2 = m2, index = idx;
        }
        return min1;
    }
};
