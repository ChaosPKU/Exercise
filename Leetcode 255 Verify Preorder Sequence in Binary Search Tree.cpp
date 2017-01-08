/*

Given an array of numbers, verify whether it is the correct preorder traversal sequence of a binary search tree.

You may assume each number in the sequence is unique.

Follow up:
Could you do it using only constant space complexity?

*/

/*
The idea is traversing the preorder list and using a stack to store all predecessors. curr_p is a predecessor of current node and current node is in the right subtree of curr_p.

For example, for the following bst with preorder 6,3,1,2,5,4,7:

              6
            /  \  
           3    7
          /  \
         1   5
         \   /
         2  4   
We push to stack before we see 2. So at 2 the stack is 6,3,1. For 2, we pop stack until we see 3 which is greater than 2 and curr_p is 1. 2 is in left subtree of 3 and is right child of 1. Stack is 6,3,2 now. Then we see 5, and we pop stack until 6 and curr_p is 3. Stack now is 6,5. Then we see 4 and push to stack. At 7, we pop stack until empty and curr_p is 6.
*/

class Solution {
public:
    bool verifyPreorder(vector<int>& preorder) {
        if(preorder.size() <= 2) return true;
        stack<int> stk;
        stk.push(preorder[0]);
        int root = INT_MIN;
        for(int i = 1;i < preorder.size(); ++ i){
            if(stk.empty() || preorder[i] < stk.top()){// if current node is less than stack top, then go to left subtree
                if(preorder[i] < root) return false;
                stk.push(preorder[i]);
            }
            else{
                while(!stk.empty() && preorder[i] > stk.top()){//find curr_p such that current node is right child of curr_p
                    root = stk.top();
                    stk.pop();
                }
                stk.push(preorder[i]);
            }
        }
        return true;
    }
};
