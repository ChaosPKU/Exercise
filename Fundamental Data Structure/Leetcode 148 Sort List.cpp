/*
Sort a linked list in O(n log n) time using constant space complexity.

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
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode *tmp = NULL;
        if(!head->next->next){
            if(head->val > head->next->val){
                tmp = head->next;
                head->next = NULL;
                tmp->next = head;
                return tmp;
            }
            else return head;
        }
        ListNode *fast = head, *slow = head, *tail = NULL;
        while(fast){
            fast = fast->next;
            tail = slow;
            slow = slow->next;
            if(fast) fast = fast->next;
        }
        tail->next = NULL;
        head = sortList(head);
        slow = sortList(slow);
        ListNode *res = new ListNode(0), *pre = res, *ptr1 = head, *ptr2 = slow;
        while(ptr1 && ptr2){
            if(ptr1->val > ptr2->val){
                pre->next = ptr2;
                ptr2 = ptr2->next;
            }
            else{
                pre->next = ptr1;
                ptr1 = ptr1->next;
            }
            pre = pre->next;
        }
        if(ptr1) pre->next = ptr1;
        if(ptr2) pre->next = ptr2;
        return res->next;
    }
};
