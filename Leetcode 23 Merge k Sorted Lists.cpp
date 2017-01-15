/*
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
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
private:
    struct cmp{
        bool operator()(ListNode*a, ListNode*b){
            return a->val > b->val;
        }
    };
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* res = NULL;
        priority_queue<ListNode*, vector<ListNode*>, cmp> q;
        for(auto l : lists) {
            if(l)  q.push(l);
        }
        ListNode *tmp = NULL;
        while(!q.empty()){
            if(!res){
                res = q.top();
            }
            if(!tmp){
                tmp = q.top();
            }
            else{
                tmp->next = q.top();
                tmp = tmp->next;
            }
            q.pop();
            if(tmp->next)
                q.push(tmp->next);
        }
        return res;
    }
};
