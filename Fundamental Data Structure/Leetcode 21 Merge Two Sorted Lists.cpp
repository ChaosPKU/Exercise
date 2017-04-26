/*
Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

Subscribe to see which companies asked this question.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *ptr1 = l1, *ptr2 = l2, *res = new ListNode(0), *pre = res;
        while(ptr1 && ptr2){
            if(ptr1->val < ptr2->val){
                pre->next = ptr1;
                ptr1 = ptr1->next;
            }
            else{
                pre->next = ptr2;
                ptr2 = ptr2->next;
            }
            pre = pre->next;
        }
        if(ptr1) pre->next = ptr1;
        else pre->next = ptr2;
        return res->next;
    }
};
