/*
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.
Example:
Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
Note:
The array is only modifiable by the update function.
You may assume the number of calls to update and sumRange function is distributed evenly.
*/

class SegmentTreeNode{
public:
    int val,start,end;
    SegmentTreeNode *left, *right;
    SegmentTreeNode(int s, int e, int v, SegmentTreeNode* l, SegmentTreeNode *r){
        start = s;
        end = e;
        val = v;
        left = l;
        right = r;
    }
};
class SegmentTree{
public:
    SegmentTreeNode *root;
    SegmentTree(vector<int> &vtr){
        root = build(vtr, 0, vtr.size() - 1);
    }
    SegmentTreeNode* build(vector<int> &vtr, int b, int e){
        if(b > e) return NULL;
        if(b == e) return new SegmentTreeNode(b, e, vtr[b], NULL, NULL);
        int m = b + (e - b) / 2;
        SegmentTreeNode *l = build(vtr, b, m), *r = build(vtr, m + 1, e);
        return new SegmentTreeNode(b, e, l->val + r->val, l, r);
    }
    int query(SegmentTreeNode *node, int b, int e){
        if(!node | b > node->end || e < node->start)
            return 0;
        if(b <= node->start && e >= node->end)
            return node->val;
        return query(node->left, b, e) + query(node->right, b, e);
    }
    int query(int b, int e){
        return query(root, b, e);
    }
    int update(SegmentTreeNode *node, int idx, int v){
        if(!node)
            return 0;
        if(idx > node->end || idx < node->start) 
            return node->val;
        if(idx == node->end && idx == node->start)
            return node->val = v;
        return node->val = update(node->left, idx, v) + update(node->right, idx, v);
    }
    int update(int idx, int v){
        return update(root, idx, v);
    }
};
class NumArray {
public:
    SegmentTree *tree;
    NumArray(vector<int> &nums) {
        tree = new SegmentTree(nums);
    }

    void update(int i, int val) {
        tree->update(i, val);
    }

    int sumRange(int i, int j) {
        return tree->query(i, j);
    }
};

// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.update(1, 10);
// numArray.sumRange(1, 2);
