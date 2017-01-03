/*
Implement strStr().

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
*/
// Brute-force version
class Solution {
public:
    int strStr(string haystack, string needle) {
        for (int i = 0; ; ++i) {
            for (int j = 0; ; ++j) {
                if (needle[j] == 0) return i;
                if (haystack[i + j] == 0) return -1;
                if (haystack[i + j] != needle[j]) break;
            }
        }
    }
};

// KMP version
class Solution {
public:
    int strStr(string haystack, string needle) {
        int hlen = haystack.size(), nlen = needle.size(), pre = 0, k = 0, i = 0, j = 0;
        if(!nlen) return 0;
        vector<int> next(nlen, 0);
        next[0] = k = -1; //next数组中的每个元素，代表当前字符之前的字符串中，有多大长度的相同前缀与后缀。
        while(j < nlen - 1){
            if(k == -1 || needle[j] == needle[k])
                next[++ j] = ++ k;
            else k = next[k];
        }
        i = j = 0;
        while(i < hlen && j < nlen){
            if(j == -1 || haystack[i] == needle[j]){
                ++ i;
                ++ j;
            }
            else j = next[j];
        }
        if(j == nlen) return i - j;
        else return -1;
    }
};

// Sunday version
class Solution {
public:
    int strStr(string haystack, string needle) {
        int hlen = haystack.size(), nlen = needle.size();
        int hashset[26] = {0}, i = 0, j = 0;
        for(int i = 0;i < nlen; ++ i)
            hashset[needle[i] - 'a'] = i + 1;
        while(i < hlen && j < nlen){
            if(haystack[i ++ ] != needle[j ++ ]){ // if == , then ++i, ++j; else...
                if((i += nlen - j) >= hlen) return -1;
                i += 1 - hashset[haystack[i] - 'a']; // if hash == 0, ++ i; else i -= hash[i];
                j = 0;
            }
        }
        if(j == nlen) return i - j;
        else return -1;
    }
};
