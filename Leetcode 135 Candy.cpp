/*
There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?
*/

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> candys(n, 1);
        for(int i = 1; i < n; i ++){
            if(ratings[i] > ratings[i - 1]){
                candys[i] = candys[i - 1] + 1;
            }
        }
        int sum = candys[n - 1];
        for(int i = n - 2; i >= 0; i --){
            if(ratings[i] > ratings[i + 1]){
                candys[i] = max(candys[i],candys[i + 1] + 1);
            }
            sum += candys[i];
        }
        return sum;
    }
};
