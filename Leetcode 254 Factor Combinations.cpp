/*
Numbers can be regarded as product of its factors. For example,

8 = 2 x 2 x 2;
  = 2 x 4.
Write a function that takes an integer n and return all possible combinations of its factors.

Note: 
You may assume that n is always positive.
Factors should be greater than 1 and less than n.
Examples: 
input: 1
output: 
[]
input: 37
output: 
[]
input: 12
output:
[
  [2, 6],
  [2, 2, 3],
  [3, 4]
]
input: 32
output:
[
  [2, 16],
  [2, 2, 8],
  [2, 2, 2, 4],
  [2, 2, 2, 2, 2],
  [2, 4, 4],
  [4, 8]
]
*/

class Solution {
public:
    void backtracking(vector<vector<int>>& res, vector<int> &vtr, vector<int> &factors, int rest, int begin){
        if(rest == 1){
            res.push_back(vtr);
            return;
        }
        if(!vtr.empty() && rest < vtr.back()) return;
        for(int i = begin; i < factors.size(); ++ i){
            if(factors[i] > rest) break;
            if(rest % factors[i] == 0){
                vtr.push_back(factors[i]);
                backtracking(res, vtr, factors, rest / factors[i], i);
                vtr.pop_back();
            }
        }
    }
    vector<vector<int>> getFactors(int n) {
        vector<vector<int>> res;
        vector<int> factors, tmp;
        for(int i = 2; i <= sqrt(n); ++ i)
            if(n % i == 0){
                factors.push_back(i);
                if(i * i != n)
                    tmp.push_back(n / i);
            }
        for(int i = tmp.size() - 1; i >= 0; -- i)
            factors.push_back(tmp[i]);
        if(!factors.size()) return res;
        vector<int> vtr;
        backtracking(res, vtr, factors, n, 0);
        return res;
    }
};
