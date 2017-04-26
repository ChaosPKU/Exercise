/*
Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(k <= 1 || !head)
        return head;
        ListNode *res = new ListNode(0);
        res->next = head;
        ListNode *pre = res, *ptr = head, *tmp = NULL, *tail = NULL;
        int cnt = 0;
        while(ptr){
            ++ cnt;
            ptr = ptr->next;
        }
        ptr = head;
        for(int i = 0;i < cnt / k; ++ i){
            tail = pre;
            head = ptr;
            pre = ptr;
            ptr = ptr->next;
            for(int j = 0;j < k - 1; ++ j){
                tmp = ptr->next;
                ptr->next = pre;
                pre = ptr;
                ptr = tmp;
            }
            tail->next = pre;
            head->next = ptr;
            pre = head;
        }
        return res->next;
    }
};


class Solution {
private:
    ListNode *reverse(ListNode *head, ListNode *tail){
        if(!head) return NULL;
        ListNode *prev = head, *ptr = head->next, *tmp = NULL;
        while(ptr != tail){
            tmp = ptr->next;
            ptr->next = prev;
            prev = ptr;
            ptr = tmp;
        }
        head->next = NULL;
        return prev;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *ptr = head, *new_head = NULL;
        for(int i = 0;i < k; ++ i){
            if(!ptr) return head;
            ptr = ptr->next;
        }
        new_head = reverse(head, ptr);
        head->next = reverseKGroup(ptr, k);
        return new_head;
    }
};
