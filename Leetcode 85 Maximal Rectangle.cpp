/*
Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 6.
*/

class Solution {
private:
    int largestRectangleArea(vector<int> heights) {
        int res = 0, idx = 0;
        stack<int> s;
        heights.insert(heights.begin(), 0);
        heights.push_back(0);
        s.push(0);
        for(int i = 1;i < heights.size(); ++ i){
            while(heights[idx = s.top()] > heights[i]){
                s.pop();
                res = max(res, heights[idx] * (i - s.top() - 1));
            }
            s.push(i);
        }
        return res;
    }
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int res = 0, n = matrix.size();
        if(!n) return 0;
        vector<int> v(matrix[0].size(), 0);
        for(int i = 0;i < matrix[0].size(); ++ i)
            if(matrix[0][i] == '1')
                v[i] = 1;
        res = largestRectangleArea(v);
        for(int i = 1;i < matrix.size(); ++ i){
            for(int j = 0;j < matrix[0].size(); ++ j){
                v[j] = matrix[i][j] == '0' ? 0 : (v[j] + 1);
            }
            res = max(res, largestRectangleArea(v));
        }
        return res;
    }
};
