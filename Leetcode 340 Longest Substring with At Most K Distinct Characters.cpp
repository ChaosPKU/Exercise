/*
Given a string, find the length of the longest substring T that contains at most k distinct characters.

For example, Given s = “eceba” and k = 2,

T is "ece" which its length is 3.
*/

// O(n) version
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        int i = 0,j = 0, maxLen = 0, n = s.size(), length = 0;
        if(n <= k) return n;
        int mp[256] = {0};
        while(j < n){
            if(mp[s[j++]] ++ == 0) ++ length;
            if(length <= k)
                maxLen ++;
            else if(-- mp[s[i ++]] == 0) 
                length --;
        }
        return maxLen;
    }
};


// O(n) 但是在处理大规模流数据的时候会有优势，相比于第一个版本，慢指针不必做O(n)扫描，总体空间也可以达到O(k)(不必把所有快指针扫过的字符存下，仅需存窗口内每个不同字符最后出现的位置，因为满指针移动的目的就是是窗口内成为不合法字符串，用类似于LRU的思想可以得到更优解)
class LRUCache{
private:
    list<pair<int, int>> used;  // <key, value>
    unordered_map<int, list<pair<int, int>>::iterator> cache;  // key -> {key, value}
    int capacity;
public:
    LRUCache(int c):capacity(c) {}
    int put(int key, int value) {
        int res = -1;
        auto it = cache.find(key);
        if (it != cache.end()) {
            used.erase(it->second);
            used.push_front({key, value});
            it->second = used.begin();
        }
        else {
            if (cache.size() == capacity) {
                res = used.back().second;
                cache.erase(used.back().first);
                used.pop_back();
            }
            used.push_front({key, value});
            cache[key] = used.begin();
        }
        return res;
    }
};
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if(k == 0) return 0;
        int i = 0,j = 0, maxLen = 0, n = s.size(), length = 0, ptr = 0;
        LRUCache lru(k);
        if(n <= k) return n;
        while(j < n){
            ptr = lru.put(s[j], j);
            ++ j;
            length ++;
            if(ptr != -1){
                length -= ptr - i + 1;
                i = ptr + 1;
            }
            maxLen = max(maxLen, length);
        }
        return maxLen;
    }
};
