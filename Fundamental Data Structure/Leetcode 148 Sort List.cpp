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


// No-recursion with stack
class Solution {
private:
    ListNode* simplesort(ListNode* head){
        if(!head || !head->next) return head;
        ListNode *tmp = NULL;
        if(head->val > head->next->val){
            tmp = head->next;
            head->next = NULL;
            tmp->next = head;
            return tmp;
        }
        else return head;
    }
    ListNode *merge(ListNode *head, ListNode *slow){
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
public:
    ListNode* sortList(ListNode* head) {
        if(!head) return NULL;
        stack<ListNode *> stk;
        stk.push(head);
        ListNode *left = NULL, *right = NULL, *res = new ListNode(0), *ptr = NULL, *fast = NULL, *slow = NULL, *tmp = NULL;
        while(!stk.empty()){
            ptr = stk.top();
            stk.pop();
            if(ptr && ptr->next && ptr->next->next){
                fast = ptr, slow = ptr, tmp = NULL;
                while(fast){
                    fast = fast->next;
                    tmp = slow;
                    slow = slow->next;
                    if(fast) fast = fast->next;
                }
                tmp->next = NULL;
                stk.push(ptr);
                stk.push(slow);
            }
            else{
                if(!left) left = simplesort(ptr);
                else{
                    right = simplesort(ptr);
                    tmp = merge(left, right);
                    if(!res->next) res->next = tmp;
                    else res->next = merge(res->next, tmp);
                    left = right = NULL;
                }
            }
        }
        if(left) res->next = merge(res->next, left);
        return res->next;
    }
};
