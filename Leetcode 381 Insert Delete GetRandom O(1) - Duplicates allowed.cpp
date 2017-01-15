/*
Design a data structure that supports all following operations in average O(1) time.

Note: Duplicate elements are allowed.
insert(val): Inserts an item val to the collection.
remove(val): Removes an item val from the collection if present.
getRandom: Returns a random element from current collection of elements. The probability of each element being returned is linearly related to the number of same value the collection contains.
Example:

// Init an empty collection.
RandomizedCollection collection = new RandomizedCollection();

// Inserts 1 to the collection. Returns true as the collection did not contain 1.
collection.insert(1);

// Inserts another 1 to the collection. Returns false as the collection contained 1. Collection now contains [1,1].
collection.insert(1);

// Inserts 2 to the collection, returns true. Collection now contains [1,1,2].
collection.insert(2);

// getRandom should return 1 with the probability 2/3, and returns 2 with the probability 1/3.
collection.getRandom();

// Removes 1 from the collection, returns true. Collection now contains [1,2].
collection.remove(1);

// getRandom should return 1 and 2 both equally likely.
collection.getRandom();
*/

class RandomizedCollection {
public:
    vector<pair<int, int>> vtr;
    unordered_map<int, vector<int>> udmp;
    /** Initialize your data structure here. */
    RandomizedCollection() {
        vtr.clear();
        udmp.clear();
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        bool flag = (udmp.find(val) == udmp.end());
        udmp[val].push_back(vtr.size());
        vtr.push_back(make_pair(val, udmp[val].size() - 1));
        return flag;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
         bool flag = (udmp.find(val) != udmp.end());
         if(flag){
             int idx = udmp[val].back();
             vtr[idx] = vtr.back();
             vtr.pop_back();
             udmp[vtr[idx].first][vtr[idx].second] = idx;
             udmp[val].pop_back();
             if(udmp[val].empty()) udmp.erase(val);
         }
         return flag;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        return vtr[rand() % vtr.size()].first;
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection obj = new RandomizedCollection();
 * bool param_1 = obj.insert(val);
 * bool param_2 = obj.remove(val);
 * int param_3 = obj.getRandom();
 */
