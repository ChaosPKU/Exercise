/*
There are some trees, where each tree is represented by (x,y) coordinate in a two-dimensional garden. Your job is to fence the entire garden using the minimum length of rope as it is expensive. The garden is well fenced only if all the trees are enclosed. Your task is to help find the coordinates of trees which are exactly located on the fence perimeter.

Example 1:
Input: [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
Output: [[1,1],[2,0],[4,2],[3,3],[2,4]]
Explanation:

Example 2:
Input: [[1,2],[2,2],[4,2]]
Output: [[1,2],[2,2],[4,2]]
Explanation:

Even you only have trees in a line, you need to use rope to enclose them. 
Note:

All trees should be enclosed together. You cannot cut the rope to enclose trees that will separate them in more than one group.
All input integers will range from 0 to 100.
The garden has at least one tree.
All coordinates are distinct.
Input points have NO order. No order required for output.
*/

// 从左下顶点开始，先找凸包下半部分，再找上半部分
// 按x,y排序后用栈存储，遇到新点是如与前面两点逆时针旋转则重复弹栈，然后压栈。

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    int cross(const Point &a, const Point &b, const Point &c){
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }
    static bool cmp(const Point &a, const Point &b){
        return a.x == b.x ? a.y < b.y : a.x < b.x; 
    }
    vector<Point> outerTrees(vector<Point>& points) {
        int n = points.size(), k = 0;
        if(n <= 3) return points;
        sort(points.begin(), points.end(), cmp);
        vector<Point> res(2 * n);
        for(int i = 0;i < n; ++ i){
            while(k >= 2 && cross(res[k - 2], res[k - 1], points[i]) < 0) -- k;
            res[k ++] = points[i];
        }
        -- k; // 重复点
        for(int i = n - 1, t = k + 1; i >= 0; -- i){
            while(k >= t && cross(res[k - 2], res[k - 1], points[i]) < 0) -- k;
            res[k ++] = points[i];
        }
        -- k;
        res.resize(k);
        return res;
    }
};
