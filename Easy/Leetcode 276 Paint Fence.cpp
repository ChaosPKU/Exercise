/*
There is a fence with n posts, each post can be painted with one of the k colors.

You have to paint all the posts such that no more than two adjacent fence posts have the same color.

Return the total number of ways you can paint the fence.

Note:
n and k are non-negative integers.
*/

//dp1[i]表示当前位置i涂的颜色与上一个涂的颜色相同时候的方法数，dp2[]表示当前涂的颜色与上一个涂的颜色不同时候的方法数。
//dp1[i] = dp2[i-1]，dp2[i] = (k - 1) * (dp1[i - 1] + dp2[i - 1]);
class Solution {
public:
    int numWays(int n, int k) {
        if(n <= 1 || k == 0) return n * k;
        int a = k * (k - 1), b = k, c = 0;
        for(int i = 2;i < n; ++ i){
            c = (k - 1) * (a + b);
            b = a;
            a = c;
        }
        return a + b;
    }
};
