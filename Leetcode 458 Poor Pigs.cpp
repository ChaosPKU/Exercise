/*
There are 1000 buckets, one and only one of them contains poison, the rest are filled with water. They all look the same. If a pig drinks that poison it will die within 15 minutes. What is the minimum amount of pigs you need to figure out which bucket contains the poison within one hour.

Answer this question, and write an algorithm for the follow-up general case.

Follow-up:

If there are n buckets and a pig drinking poison will die within m minutes, how many pigs (x) you need to figure out the "poison" bucket within p minutes? There is exact one bucket with poison.

Subscribe to see which companies asked this question.
*/

// 编码问题，n个猪m个状态的时候可以对m进制表示的n位数进行编码，共可以表示m^n。

class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        if(buckets == 1) return 0;
        return (ceil)(log(buckets) / (float)log(1 + minutesToTest / minutesToDie));
    }
};
