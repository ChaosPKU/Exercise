/*
You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example:

Given nums = [5, 2, 6, 1]

To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
Return the array [2, 1, 1, 0].
*/

// Merge Sort Version
// 某个数字之后比它小的数字个数等于在merge sort过程中排序从后到前超过该数的数字个数。
/*
class Solution {
public:
    void merge(vector<pair<int, int>> &vtr, vector<pair<int, int>> &copy, vector<int> &res, int b, int e){
        if(b == e) return;
        int m = b + (e - b) / 2;
        merge(vtr, copy, res, b, m);
        merge(vtr, copy, res, m + 1, e);
        int i = m, j = e, k = e;
        while(i >= b || j >= m + 1){
            if(i < b || (j > m && copy[j].second >= copy[i].second))
                vtr[k--] = copy[j--];
            else{
                res[copy[i].first] += j - m;
                vtr[k--] = copy[i--];
            }
        }
        for(int i = b; i <= e; ++ i)
            copy[i] = vtr[i];
    }
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 0);
        if(n == 0) return res;
        vector<pair<int, int>> vtr(n), copy(n);
        for(int i = 0;i < n; ++ i)
            vtr[i] = copy[i] = make_pair(i, nums[i]);
        merge(vtr, copy, res, 0, n - 1);
        return res;
    }
};
*/
// Segment Tree Version
/*
class SegmentTreeNode{
public:
    int val, start, end;
    SegmentTreeNode *left, *right;
    SegmentTreeNode(int s, int e, SegmentTreeNode *l, SegmentTreeNode *r){
        start = s;
        end = e;
        val = 0;
        left = l;
        right = r;
    };
};
class SegmentTree{
public:
    SegmentTreeNode *root;
    SegmentTreeNode* build(int b, int e){
        if(b > e) return NULL;
        if(b == e) return new SegmentTreeNode(b, e, NULL, NULL);
        int m = b + (e - b) / 2;
        return new SegmentTreeNode(b, e, build(b, m), build(m + 1, e));
    }
    SegmentTree(int n){
        root = build(0, n - 1);
    }
    int update(SegmentTreeNode *node, int n, int v){
        if(!node) return 0;
        if(n < node->start || n > node->end)
            return node->val;
        if(n == node->start && n == node->end){
            node->val += v;
            return node->val;
        }
        return node->val = update(node->left, n, v) + update(node->right, n, v);
    }
    int query(SegmentTreeNode *node, int b, int e){
        if(!node || b > node->end || e < node->start) return 0;
        if(b <= node->start && e >= node->end)
            return node->val;
        return query(node->left, b, e) + query(node->right, b, e);
    }
};
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> udmp;
        vector<int> copy(nums.begin(), nums.end());
        sort(copy.begin(), copy.end());
        for(int i = 0;i < n; ++ i)
            udmp[copy[i]] = i;
        SegmentTree *st = new SegmentTree(nums.size());
        vector<int> res(n, 0);
        for(int i = n - 1;i >= 0; -- i){
            res[i] = st->query(st->root, 0, udmp[nums[i]] - 1);
            st->update(st->root, udmp[nums[i]], 1);
        }
        return res;
    }
};
*/
// Binary Index Tree Version
/*
class BinaryIndexedTree {
private:
    vector<int> sums;
public:
    BinaryIndexedTree(int n){
        sums.resize(n + 1);
    }
    void update(int index){
        while(index < sums.size()){
            sums[index] += 1;
            index += index & -index;
        }
    }
    int sum(int index){
        int res = 0;
        while(index > 0){
            res += sums[index];
            index -= index & -index;
        }
        return res;
    }
};
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        set<int> myset(nums.begin(), nums.end());
        unordered_map<int, int> mymap;
        int cnt = 0;
        for(auto iter = myset.begin(); iter != myset.end(); ++ iter){
            mymap[*iter] = cnt ++;
        }
        BinaryIndexedTree tree = BinaryIndexedTree(mymap.size());
        vector<int> res(nums.size(), 0);
        for(int i = nums.size() - 1; i >= 0; -- i){
            res[i] = tree.sum(mymap[nums[i]]);
            tree.update(mymap[nums[i]] + 1);
        }
        return res;
    }
};
*/
