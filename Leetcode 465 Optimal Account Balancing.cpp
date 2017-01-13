/*
A group of friends went on holiday and sometimes lent each other money. For example, Alice paid for Bill's lunch for $10. Then later Chris gave Alice $5 for a taxi ride. We can model each transaction as a tuple (x, y, z) which means person x gave person y $z. Assuming Alice, Bill, and Chris are person 0, 1, and 2 respectively (0, 1, 2 are the person's ID), the transactions can be represented as [[0, 1, 10], [2, 0, 5]].

Given a list of transactions between a group of people, return the minimum number of transactions required to settle the debt.

Note:

A transaction will be given as a tuple (x, y, z). Note that x ≠ y and z > 0.
Person's IDs may not be linear, e.g. we could have the persons 0, 1, 2 or we could also have the persons 0, 2, 6.
Example 1:

Input:
[[0,1,10], [2,0,5]]

Output:
2

Explanation:
Person #0 gave person #1 $10.
Person #2 gave person #0 $5.

Two transactions are needed. One way to settle the debt is person #1 pays person #0 and #2 $5 each.
Example 2:

Input:
[[0,1,10], [1,0,1], [1,2,5], [2,0,5]]

Output:
1

Explanation:
Person #0 gave person #1 $10.
Person #1 gave person #0 $1.
Person #1 gave person #2 $5.
Person #2 gave person #0 $5.

Therefore, person #1 only need to give person #0 $4, and all debt is settled.

*/

class Solution {
public:
    int minTransfers(vector<vector<int>>& transactions) {
        unordered_map<int, int> udmp;
        for(vector<int> vtr : transactions){
            udmp[vtr[0]] -= vtr[2];
            udmp[vtr[1]] += vtr[2];
        }
        vector<int> in, out;
        int amount = 0;
        for(auto p : udmp)
            if(p.second > 0) {
                in.push_back(p.second);
                amount += p.second;
            }
            else if(p.second < 0) out.push_back(-p.second);
        if(!amount) return 0;
        int res = in.size() + out.size() - 1;
        DFS(in, out, 0, 0, amount, 0, res);
        return res;
    }
    void DFS(vector<int> &in, vector<int> &out, int i, int k, int amount, int step, int &res){
        if(step >= res) return;
        if(!amount) {
            res = step;
            return;
        }
        while(!in[i]) {
            ++ i;
            k = 0;
        }
        for(int j = k; j < out.size(); ++ j){
            if(!out[j]) continue;
            int dec = min(in[i], out[j]);
            in[i] -= dec;
            out[j] -= dec;
            DFS(in, out, i, j + 1, amount - dec, step + 1, res);
            in[i] += dec;
            out[j] += dec;
        }
        
    }
};
