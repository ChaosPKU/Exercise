/*
A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.
*/

/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(!head) return NULL;
        unordered_map<RandomListNode*, RandomListNode*> m;
        RandomListNode *res = new RandomListNode(head->label), *ptr = res, *tmp = head;
        m[head] = res;
        while(tmp->next){
            ptr->next = new RandomListNode(tmp->next->label);
            tmp = tmp->next;
            ptr = ptr->next;
            m[tmp] = ptr;
        }
        tmp = head;
        ptr = res;
        while(tmp){
            ptr->random = m[tmp->random];
            ptr = ptr->next;
            tmp = tmp->next;
        }
        return res;
    }
};
