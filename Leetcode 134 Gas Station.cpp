/*
There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique.
*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        if(!n) return -1;
        int sum = 0, min = 0, tag = 0;
        sum = min = gas[0] - cost[0];
        for(int i = 1; i < n; ++ i){
            sum += gas[i] - cost[i];
            if(sum < min){
                min = sum;
                tag = i;
            }
        }
        return sum >= 0 ? (tag + 1 == n ? 0 : tag + 1) : -1;
    }
};
