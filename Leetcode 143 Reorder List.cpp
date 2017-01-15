/*
Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.
*/

class Solution {
private:
    ListNode* reverseList(ListNode* head){
        ListNode *pre = head, *ptr = head->next, *nxt = NULL;
        while(ptr){
            nxt = ptr->next;
            ptr->next = pre;
            pre = ptr;
            ptr = nxt;
        }
        head->next = NULL;
        return pre;
    }
    void genLists(ListNode *l1, ListNode *l2){
        ListNode *p1 = l1, *p2 = l2, *n1 = NULL, *n2 = NULL;
        while(p1 && p2){
            n1 = p1->next;
            n2 = p2->next;
            p1->next = p2;
            p2->next = n1;
            p1 = n1;
            p2 = n2;
        }
    }
public:
    void reorderList(ListNode* head) {
        if(!head || !head->next) return;
        ListNode *fast = head, *slow = head, *pre_slow = NULL;
        while(fast){
            fast = fast->next;
            pre_slow = slow;
            slow = slow->next;
            if(fast)
                fast = fast->next;
        }
        pre_slow->next = NULL;
        ListNode *tail = reverseList(slow);
        genLists(head, tail);
    }
};
