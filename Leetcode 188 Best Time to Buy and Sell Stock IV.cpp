/*
Say you have an array for which the i th element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most k transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if(k == 0) return 0;
        if(k >= prices.size() / 2){
            int res = 0;
            for(int i = 1;i < prices.size(); ++ i)
                res += max(0,prices[i] - prices[i-1]);
            return res;
        }
        vector<int> h(k,-prices[0]); //hold
        vector<int> r(k,0); // release 
        for(int i = 0;i < prices.size(); ++ i){
            for(int j = k-1; j >= 0; -- j){
                r[j] = max(r[j],h[j] + prices[i]);  // result
                if(j >= 1)
                    h[j] = max(h[j],r[j-1] - prices[i]);
                else
                    h[j] = max(h[j], - prices[i]);
            }
        }
        return r[k-1];
    }
};
