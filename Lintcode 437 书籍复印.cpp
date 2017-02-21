/*
给出一个数组A包含n个元素，表示n本书以及各自的页数。现在有个k个人复印书籍，每个人只能复印连续一段编号的书，比如A[1],A[2]由第一个人复印，但是不能A[1],A[3]由第一个人复印，求最少需要的时间复印所有书。
样例
A = [3,2,4],k = 2
返回5，第一个人复印前两本书
*/
class Solution {
public:
    /**
     * @param pages: a vector of integers
     * @param k: an integer
     * @return: an integer
     */
    int copyBooks(vector<int> &pages, int k) {
        int n = pages.size();
        if(!n) return 0;
        if(k > n) k = n;
        vector<int> sums(pages.begin(), pages.end());
        for(int i = 1;i < n; ++ i)
            sums[i] += sums[i - 1];
        vector<int> res(sums.begin(), sums.end());
        for(int i = 2;i <= k; ++ i){
            for(int j = 1;j < i - 1; ++ j)
                res[j] = max(res[j - 1], pages[j - 1]);
            int m = n;
            //s从n到i的过程中，m一定是递减的，据此可以降低复杂度。
            for(int s = n; s >= i; -- s){
                while(res[m - 1] > sums[s - 1] - sums[m - 1]) -- m;
                res[s - 1] = max(res[m - 1], sums[s - 1] - sums[m - 1]);
                if(m < s) ++ m;
                res[s - 1] = min(res[s - 1], max(res[m - 1], sums[s - 1] - sums[m - 1]));
            }
        }
        return res[n - 1];
    }
};
