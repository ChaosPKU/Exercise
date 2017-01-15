/*
Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.
Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].
The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given heights = [2,1,5,6,2,3],
return 10.
*/

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
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
};
