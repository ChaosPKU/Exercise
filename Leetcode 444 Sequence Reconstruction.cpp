/*
Check whether the original sequence org can be uniquely reconstructed from the sequences in seqs. The org sequence is a permutation of the integers from 1 to n, with 1 ≤ n ≤ 104. Reconstruction means building a shortest common supersequence of the sequences in seqs (i.e., a shortest sequence so that all sequences in seqs are subsequences of it). Determine whether there is only one sequence that can be reconstructed from seqs and it is the org sequence.

Example 1:

Input:
org: [1,2,3], seqs: [[1,2],[1,3]]

Output:
false

Explanation:
[1,2,3] is not the only one sequence that can be reconstructed, because [1,3,2] is also a valid sequence that can be reconstructed.
Example 2:

Input:
org: [1,2,3], seqs: [[1,2]]

Output:
false

Explanation:
The reconstructed sequence can only be [1,2].
Example 3:

Input:
org: [1,2,3], seqs: [[1,2],[1,3],[2,3]]

Output:
true

Explanation:
The sequences [1,2], [1,3], and [2,3] can uniquely reconstruct the original sequence [1,2,3].
Example 4:

Input:
org: [4,1,5,2,6,3], seqs: [[5,2,6,3],[4,1,5,2]]

Output:
true
*/

// 对于这道题目来说，并没有必要构建图求完整的拓扑排序。只需要确保序列串中每一条边均出现过且没有不合法点和不合法先后关系出现即可。
class Solution {
public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        int len = org.size(), counter = len - 1;
        if(seqs.empty()) return false;
        vector<int> udmp(len + 1, 0);
        vector<bool> flags(len + 1, 0);
        for(int i = 0; i < len; ++ i) udmp[org[i]] = i;
        for(int i = 0;i < seqs.size(); ++ i){
            for(int j = 0;j < seqs[i].size(); ++ j){
                if(seqs[i][j] < 1 || seqs[i][j] > len) return false;
                if(j == 0) continue;
                int pre = udmp[seqs[i][j - 1]], cur = udmp[seqs[i][j]];
                if(pre >= cur) return false;
                if(flags[pre] == 0 && pre + 1 == cur) flags[pre] = 1, -- counter;
            }
        }
        return counter == 0;
    }
};

//MLE
class Solution {
public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        int olen = org.size(), srows = seqs.size(), scols = 0, cnt = 0;
        if(!olen && !srows) return true;
        if(!olen || !srows) return false;
        for(int i = 0;i < srows; ++ i) {
            scols = seqs[i].size();
            for(int j = 0;j < scols; ++ j)
                if(seqs[i][j] < 1 || seqs[i][j] > olen) return false;
        }
        vector<int> udmp(olen);
        vector<unordered_set<int>> next(olen), pre(olen);
        for(int i = 0;i < org.size(); ++ i) udmp[org[i] - 1] = i;
        for(int i = 0;i < srows; ++ i) { 
            scols = seqs[i].size();
            if(scols <= 1) continue;
            if(udmp[seqs[i][0] - 1] > udmp[seqs[i][1] - 1]) return false;
            pre[seqs[i][scols - 1] - 1].insert(seqs[i][scols - 2] - 1);
            next[seqs[i][0] - 1].insert(seqs[i][1] - 1);
            for(int j = 1;j < scols - 1; ++ j){
                if(udmp[seqs[i][j] - 1] > udmp[seqs[i][j + 1] - 1]) return false;
                next[seqs[i][j] - 1].insert(seqs[i][j + 1] - 1);
                pre[seqs[i][j] - 1].insert(seqs[i][j - 1] - 1);
            }
        }
        for(int i = 1;i < olen; ++ i)
            if(pre[org[i] - 1].size() == 0) return false;
        for(int i = 0;i < olen; ++ i){
            if(pre[org[i] - 1].size() > 0) return false;
            cnt = 0;
            for(int n : next[org[i] - 1]){
                pre[n].erase(org[i] - 1);
                if(pre[n].size() == 0) cnt ++;
            }
            if(cnt > 1) return false;
        }
        return true;
    }
};
