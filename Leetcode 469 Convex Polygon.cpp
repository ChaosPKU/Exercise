/*
Given a list of points that form a polygon when joined sequentially, find if this polygon is convex (Convex polygon definition).

Note:

There are at least 3 and at most 10,000 points.
Coordinates are in the range -10,000 to 10,000.
You may assume the polygon formed by given points is always a simple polygon (Simple polygon definition). In other words, we ensure that exactly two edges intersect at each vertex, and that edges otherwise don't intersect each other.
Example 1:

[[0,0],[0,1],[1,1],[1,0]]

Answer: True
Example 2:

[[0,0],[0,10],[10,10],[10,0],[5,5]]

Answer: False
*/
//用向量叉乘。注意区分前后向量方向一致的情况单独讨论。
class Solution {
public:
    int calc(const vector<vector<int>>& vtr, int& i){
        int n = vtr.size(), a = i == 0 ? n - 1 : i - 1, b = i, c = i == n - 1 ? 0 : i + 1;
        return (vtr[b][0] - vtr[a][0]) * (vtr[c][1] - vtr[b][1]) - (vtr[c][0] - vtr[b][0]) * (vtr[b][1] - vtr[a][1]);
    }
    bool isConvex(vector<vector<int>>& points) {
        if(points.size() < 3) return false;
        int n = points.size(), pre = -1;
        for(int i = 0;i < n; ++ i){
            int tmp = calc(points, i);
            if(!tmp) continue;
            if(pre == -1) pre = tmp > 0;
            else if(pre != tmp > 0) return false;
        }
        return true;
    }
};
