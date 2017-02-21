/* 扔 n 个骰子，向上面的数字之和为 S。给定 Given n，请列出所有可能的 S 值及其相应的概率。
样例
给定 n = 1，返回 [ [1, 0.17], [2, 0.17], [3, 0.17], [4, 0.17], [5, 0.17], [6, 0.17]]。
*/
class Solution {
public:
    /**
     * @param n an integer
     * @return a list of pair<sum, probability>
     */
    vector<pair<int, double>> dicesSum(int n) {
        vector<double> res(6 * n + 1, 0);
        for(int i = 1;i <= 6; ++i)
            res[i] = 1.0/6;
        for(int i = 2;i <= n; ++ i)
            for(int j = 6 * i; j >= i; -- j){
                double sum = 0;
                for(int k = 1;k <= 6 && j - k >= i - 1; ++ k)
                //需要注意的是，i - 1以内的数据不属于第n - 1次投掷，需要被过滤掉
                    sum += res[j - k] * 1.0/6;
                res[j] = sum;
            }
        vector<pair<int, double> > ans(5 * n + 1, make_pair(0, 0));
        for(int i = 0;i < ans.size(); ++ i)
            ans[i] = make_pair(n + i, res[n + i]);
        return ans;
    }
};
