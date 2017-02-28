/*

Suppose you have N integers from 1 to N. We define a beautiful arrangement as an array that is constructed by these N numbers successfully if one of the following is true for the ith position (1 ≤ i ≤ N) in this array:

The number at the ith position is divisible by i.
i is divisible by the number at the ith position.
Now given N, how many beautiful arrangements can you construct?

Example 1:
Input: 2
Output: 2
Explanation: 

The first beautiful arrangement is [1, 2]:

Number at the 1st position (i=1) is 1, and 1 is divisible by i (i=1).

Number at the 2nd position (i=2) is 2, and 2 is divisible by i (i=2).

The second beautiful arrangement is [2, 1]:

Number at the 1st position (i=1) is 2, and 2 is divisible by i (i=1).

Number at the 2nd position (i=2) is 1, and i (i=2) is divisible by 1.
Note:
N is a positive integer and will not exceed 15.

*/

class Solution {
public:
    int backtracking(vector<int> &nums, int b){
        if(b <= 0) return 1;
        int res = 0;
        for(int i = 0;i < b; ++ i)
            if((b % nums[i] == 0) || (nums[i] % b == 0)){
                swap(nums[i], nums[b - 1]);
                res += backtracking(nums, b - 1);
                swap(nums[i], nums[b - 1]);
            }
        return res;
    }
    int countArrangement(int N) {
        vector<int> nums(N);
        for(int i = 0; i < N; ++ i)
            nums[i] = i + 1;
        return backtracking(nums, N);
    }
};


class Solution {
public:
    void backtracking(vector<vector<int>> &nums, unordered_set<int> &udst, int &res, int b, int &N){
        if(b > N){
            ++ res;
            return;
        }
        for(int i = 0;i < nums[b].size(); ++ i)
            if(udst.find(nums[b][i]) == udst.end()){
                udst.insert(nums[b][i]);
                backtracking(nums, udst, res, b + 1, N);
                udst.erase(nums[b][i]);
            }
        return;
    }
    int countArrangement(int N) {
        vector<vector<int>> nums(N + 1, vector<int>{1});
        for(int i = 2;i <= N; ++ i){
            nums[1].push_back(i);
            nums[i].push_back(i);
            for(int j = 2;j <= N / i; ++ j){
                nums[i].push_back(i * j);
                nums[i * j].push_back(i);
            }
        }
        int res = 0;
        unordered_set<int> udst;
        backtracking(nums, udst, res, 1, N);
        return res;
    }
};
