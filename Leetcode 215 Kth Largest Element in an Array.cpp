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
#include <iostream>  
#include <string.h>  
#include <stdio.h>  
#include <time.h>  
#include <algorithm>  
   
using namespace std;  
const int N = 10005;  
   
int a[N];  
   
//插入排序  
void InsertSort(int a[], int l, int r)  
{  
    for(int i = l + 1; i <= r; i++)  
    {  
        if(a[i - 1] > a[i])  
        {  
            int t = a[i];  
            int j = i;  
            while(j > l && a[j - 1] > t)  
            {  
                a[j] = a[j - 1];  
                j--;  
            }  
            a[j] = t;  
        }  
    }  
}  
   
//寻找中位数的中位数  
int FindMid(int a[], int l, int r)  
{  
    if(l == r) return a[l];  
    int i = 0;  
    int n = 0;  
    for(i = l; i < r - 5; i += 5)  
    {  
        InsertSort(a, i, i + 4);  
        n = i - l;  
        swap(a[l + n / 5], a[i + 2]);  
    }  
   
    //处理剩余元素  
    int num = r - i + 1;  
    if(num > 0)  
    {  
        InsertSort(a, i, i + num - 1);  
        n = i - l;  
        swap(a[l + n / 5], a[i + num / 2]);  
    }  
    n /= 5;  
    if(n == l) return a[l];  
    return FindMid(a, l, l + n);  
}  
   
//寻找中位数的所在位置  
int FindId(int a[], int l, int r, int num)  
{  
    for(int i = l; i <= r; i++)  
        if(a[i] == num)  
            return i;  
    return -1;  
}  
   
//进行划分过程  
int Partion(int a[], int l, int r, int p)  
{  
    swap(a[p], a[l]);  
    int i = l;  
    int j = r;  
    int pivot = a[l];  
    while(i < j)  
    {  
        while(a[j] >= pivot && i < j)  
            j--;  
        a[i] = a[j];  
        while(a[i] <= pivot && i < j)  
            i++;  
        a[j] = a[i];  
    }  
    a[i] = pivot;  
    return i;  
}  
   
int BFPTR(int a[], int l, int r, int k)  
{  
    int num = FindMid(a, l, r);    //寻找中位数的中位数  
    int p =  FindId(a, l, r, num); //找到中位数的中位数对应的id  
    int i = Partion(a, l, r, p);  
   
    int m = i - l + 1;  
    if(m == k) return a[i];  
    if(m > k)  return BFPTR(a, l, i - 1, k);  
    return BFPTR(a, i + 1, r, k - m);  
}  
   
int main()  
{  
    int n, k;  
    scanf("%d", &n);  
    for(int i = 0; i < n; i++)  
        scanf("%d", &a[i]);  
    scanf("%d", &k);  
    printf("The %d th number is : %d\n", k, BFPTR(a, 0, n - 1, k));  
    for(int i = 0; i < n; i++)  
        printf("%d ", a[i]);  
    puts("");  
    return 0;  
}  
