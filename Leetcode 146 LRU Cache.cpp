/*
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
*/

class LRUCache{
  private:
    int capacity;
    int counter;
    struct Node{
      int key;
      int val;
      Node* next;
      Node* pre;
      Node(int k, int v){
        key = k;
        val = v;
        pre = NULL;
        next = NULL;
      }
      Node(int k, int v, Node* p, Node* n){
        key = k;
        val = v;
        next = n;
        pre = p;
      }
    };
    unordered_map<int, Node*> m;
    Node* head, *tail;
  public:
    LRUCache(int c) {
      capacity = c;
      counter = 0;
      head = NULL;
      tail = NULL;
      m.clear();
    }
    
    int get(int key) {
      auto iter = m.find(key);
      if(iter == m.end())
        return -1;
      else{
        Node *ptr = iter->second;
        Node *pre = ptr->pre, *nxt = ptr->next;
        
        if(pre)
          pre->next = nxt;
        if(nxt && pre)
          nxt->pre = pre;
        if(!nxt && pre)
          tail = pre;
        
        if(ptr != head){
          ptr->next = head;
          head->pre = ptr;
          ptr->pre = NULL;
          head = ptr;
        }

        return ptr->val;
      }
    }
    
    void set(int key, int value) {
      auto iter = m.find(key);
      if(iter == m.end()){
        counter += 1;
        Node *n = new Node(key, value);
        m[key] = n;
        
        if(!head)
          head = tail = n;
        else{
          n->next = head;
          head->pre = n;
          head = n;
        }
        while(counter > capacity){
          tail = tail->pre;
          m.erase(tail->next->key);
          tail->next = NULL;
          -- counter;
        }
      }
      else{
        iter->second->val = value;
        Node *ptr = iter->second;
        Node *pre = ptr->pre, *nxt = ptr->next;
        
        if(pre)
          pre->next = nxt;
        if(nxt && pre)
          nxt->pre = pre;
        if(!nxt && pre)
          tail = pre;
        
        if(ptr != head){
          ptr->next = head;
          head->pre = ptr;
          ptr->pre = NULL;
          head = ptr;
        }
      }
      return;
    }
  };
