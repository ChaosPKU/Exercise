/*
Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.
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
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head || !k) return head;
        ListNode *tail = head, *fast = head, *new_head = NULL;
        int n = 1, i = 0;
        while(tail->next){
            n ++;
            tail = tail->next;
        }
        k %= n;
        if(!k) return head;
        while(++ i < n - k)
            fast = fast->next;
        new_head = fast->next;
        fast->next = NULL;
        tail->next = head;
        return new_head;
    }
};
