/*
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Write a function to determine if a number is strobogrammatic. The number is represented as a string.

For example, the numbers "69", "88", and "818" are all strobogrammatic.
*/
class Solution {
public:
    bool isStrobogrammatic(string num) {
        int b = 0, e = num.size() - 1;
        while(b < e){
            if((num[b] == '1' && num[e] == '1') || (num[b] == '8' && num[e] == '8') || (num[b] == '6' && num[e] == '9') || (num[b] == '9' && num[e] == '6') || (num[b] == '0' && num[e] == '0')){
                ++ b;
                -- e;
                continue;
            }
            return false;
            
        }
        return b == e ? (num[b] == '8' || num[b] == '1' || num[b] == '0') : true;
    }
};
