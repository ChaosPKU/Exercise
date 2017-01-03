/*
Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

Note: 
You may assume k is always valid, 1 ≤ k ≤ array's length.

Credits:
Special thanks to @mithmatt for adding this problem and creating all test cases.
*/
// Recursive version: Average O(n), Worse O(n ^ 2);
class Solution {
public:
    int helper(int k, vector<int>& nums, int b, int e){
        int pivot = nums[b], pb = b, pe = e, ptr = b;
        while(b <= e){
            if(nums[b] == pivot) ++ b;
            else if(nums[b] < pivot) swap(nums[b], nums[e --]);
            else swap(nums[ptr++], nums[b ++]);
        }
        if(ptr == k)
            return nums[ptr];
        else if(ptr > k)
            return helper(k, nums, pb, ptr);
        else
            return helper(k, nums, ptr + 1, pe);
    }
    int findKthLargest(vector<int>& nums, int k) {
        return helper(k - 1, nums, 0, nums.size() - 1);
    }
};
// None-recursive partition version
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        -- k;
        int b = 0, e = nums.size() - 1, ptr = 0, pivot = 0, pb = 0, pe = 0;
        while(true){
            pb = b, pe = e;
            pivot = nums[pb];
            while(pb < pe){
                while(pb < pe && nums[pe] <= pivot) pe --;
                nums[pb] = nums[pe];
                while(pb < pe && nums[pb] >= pivot) pb ++;
                nums[pe] = nums[pb];
            }
            nums[pb] = pivot;
            if(pb == k) return nums[pb];
            else if(pb > k) e = pb - 1;
            else b = pb + 1;
        }
    }
};

// Random select pivot version from none-Recursive partition version
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        -- k;
        int b = 0, e = nums.size() - 1, ptr = 0, pivot = 0, pb = 0, pe = 0;
        while(true){
            pb = b, pe = e;
            pivot = nums[ptr = rand() % (pe - pb + 1) + pb];
            swap(nums[pb], nums[ptr]);
            while(pb < pe){
                while(pb < pe && nums[pe] <= pivot) pe --;
                nums[pb] = nums[pe];
                while(pb < pe && nums[pb] >= pivot) pb ++;
                nums[pe] = nums[pb];
            }
            nums[pb] = pivot;
            if(pb == k) return nums[pb];
            else if(pb > k) e = pb - 1;
            else b = pb + 1;
        }
    }
};

// C++ algorithm version
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        nth_element(nums.begin(),nums.begin() + (nums.size() - k), nums.end());
        return nums[nums.size() - k];
    }
};

// STL priorit-queue version
struct compare {
    bool operator()(int& l, int& r)
        return l > r;
};
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, compare> Q;
        for (auto num : nums) {
            Q.push(num);
            if (Q.size() > k)
                Q.pop();
        }
        return Q.top();
    }
};

// STL multiset version
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        multiset<int> mset;
        int n = nums.size();
        for (int i = 0; i < n; i++) { 
            mset.insert(nums[i]);
            if (mset.size() > k)
                mset.erase(mset.begin());
        }
        return *mset.begin();
    }
};

// Heap sort version from https://discuss.leetcode.com/topic/15256/4-c-solutions-using-partition-max-heap-priority_queue-and-multiset-respectively/2
class Solution {
public:   
    inline int left(int idx) {
        return (idx << 1) + 1;
    }
    inline int right(int idx) {
        return (idx << 1) + 2;
    }
    void max_heapify(vector<int>& nums, int idx) {
        int largest = idx;
        int l = left(idx), r = right(idx);
        if (l < heap_size && nums[l] > nums[largest]) largest = l;
        if (r < heap_size && nums[r] > nums[largest]) largest = r;
        if (largest != idx) {
            swap(nums[idx], nums[largest]);
            max_heapify(nums, largest);
        }
    }
    void build_max_heap(vector<int>& nums) {
        heap_size = nums.size();
        for (int i = (heap_size >> 1) - 1; i >= 0; i--)
            max_heapify(nums, i);
    }
    int findKthLargest(vector<int>& nums, int k) {
        build_max_heap(nums);
        for (int i = 0; i < k; i++) {
            swap(nums[0], nums[heap_size - 1]);
            heap_size--;
            max_heapify(nums, 0);
        }
        return nums[heap_size];
    }
private:
    int heap_size;
}

// BFPRT version : Worse O(n) from http://blog.csdn.net/acdreamers/article/details/44656295

class Solution {
public:
    void InsertSort(vector<int>& nums, int l, int r){ //快速排序
        for(int i = l + 1; i <= r; ++ i){
            if(nums[i - 1] < nums[i]){
                int tmp = nums[i], j = i;
                while(j > l && nums[j - 1] < tmp){
                    nums[j] = nums[j - 1];
                    -- j;
                }
                nums[j] = tmp;
            }
        }
    }
    int FindMid(vector<int> &nums, int l, int r){ //寻找分段中位数的中位数
        if(l == r) return nums[l];
        int i = 0, n = 0;
        for(i = l; i < r - 5; i += 5){
            InsertSort(nums, i, i + 4);
            n = i - l;
            swap(nums[l + n / 5], nums[i + 2]);
        }
        int len = r - i + 1;
        if(len > 0){
            InsertSort(nums, i, i + len - 1);
            n = i - l;
            swap(nums[l + n / 5], nums[i + len / 2]);
        }
        return FindMid(nums, l, l + n / 5);
    }
    int FindID(vector<int> &nums, int l, int r, int n){
        for(int i = l; i <= r; ++ i)
            if(nums[i] == n) return i;
        return -1;
    }
    int Partition(vector<int> &nums, int l, int r, int p){
        swap(nums[p], nums[l]);
        int i = l, j = r, pivot = nums[l];
        while(i < j){
            while(nums[j] <= pivot && i < j) -- j;
            nums[i] = nums[j];
            while(nums[i] >= pivot && i < j) ++ i;
            nums[j] = nums[i];
        }
        nums[i] = pivot;
        return i;
    }
    int BFPTR(vector<int> &nums, int l, int r, int k){
        int num = 0, p = 0, i = 0, res = 0;
        num = FindMid(nums, l, r);
        p = FindID(nums, l, r, num);
        i = Partition(nums, l, r, p);
        res = i - l + 1;
        if(res == k) return nums[i];
        if(res > k) return BFPTR(nums, l, i - 1, k);
        return BFPTR(nums, i + 1, r, k - res);
    }
    int findKthLargest(vector<int>& nums, int k) {
        return BFPTR(nums, 0, nums.size() - 1,  k);
    }
};
