/*
In the "100 game," two players take turns adding, to a running total, any integer from 1..10. The player who first causes the running total to reach or exceed 100 wins.

What if we change the game so that players cannot re-use integers?

For example, two players might take turns drawing from a common pool of numbers of 1..15 without replacement until they reach a total >= 100.

Given an integer maxChoosableInteger and another integer desiredTotal, determine if the first player to move can force a win, assuming both players play optimally.

You can always assume that maxChoosableInteger will not be larger than 20 and desiredTotal will not be larger than 300.

Example

Input:
maxChoosableInteger = 10
desiredTotal = 11

Output:
false

Explanation:
No matter which integer the first player choose, the first player will lose.
The first player can choose an integer from 1 up to 10.
If the first player choose 1, the second player can only choose integers from 2 up to 10.
The second player will win by choosing 10 and get a total = 11, which is >= desiredTotal.
Same with other integers chosen by the first player, the second player will always win.
*/

class Solution {
public:
    // bool canIWin(int maxChoosableInteger, int desiredTotal) {
    bool canWin(int key, int d, unordered_map<int, bool> &cache, int m){
        if(cache.find(key) != cache.end())
            return cache[key];
        if(d == 0 || d <= m && (key > 1 << d - 1))
            return cache[key] = true;
        for(int i = m - 1; i >= 0; -- i){
            if(key & (1 << i)){
                key ^= (1 << i);
                if(!canWin(key, d - i - 1, cache, m)){
                    key |= (1 << i);
                    return cache[key] = true;
                }
                key |= (1 << i);
            }
        }
        return cache[key] = false;
    }
    bool canIWin(int m, int d) {
        if(d <= m) return true;
        int sum = (m + 1) * m / 2;
        if(sum < d) return false;
        if(sum == d) return m & 1;
        unordered_map<int, bool> cache(d);
        int key = (1 << m) - 1;
        return canWin(key, d, cache, m);
    }
};
