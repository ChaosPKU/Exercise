/*

There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5

*/

// 二分之后答案只可能在nums1[l-1], nums1[l], nums2[k-l], 和nums2[k-l+1]中取
// 如果总长是奇数，那么中位数median = max(nums1[l-1], nums2[k-l])
// 如果总长是偶数，那么中位数median = (max(A[l-1], B[k-l]) + min(A[l], B[k-l+1]) / 2.0

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        if(n1 > n2) return findMedianSortedArrays(nums2, nums1);
        int mlen = (n1 + n2 - 1) / 2, l = 0, r = min(n1, mlen), mid1, mid2, r1, r2;
        while(l < r){
            mid1 = (l + r) / 2;
            mid2 = mlen - mid1;
            if(nums1[mid1] < nums2[mid2])
                l = mid1 + 1;
            else r = mid1;
        }
        r1 = max(l > 0 ? nums1[l - 1] : INT_MIN, mlen - l >= 0 ? nums2[mlen - l] : INT_MIN);
        if((n1 + n2) & 1) return r1 + 0.0;
        r2 = min(l < n1 ? nums1[l] : INT_MAX, mlen - l + 1 < n2 ? nums2[mlen - l + 1] : INT_MAX);
        return (r1 + r2) / 2.0;
    };
};


// From https://discuss.leetcode.com/topic/4996/share-my-o-log-min-m-n-solution-with-explanation
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        if(n1 > n2) return findMedianSortedArrays(nums2, nums1);
        int begin = 0, end = n1, mlen = (n1 + n2 + 1) / 2;
        int lmax = 0, rmin = 0, m = 0;
        while(begin <= end){
            m = begin + (end - begin) / 2;
            if(mlen - m > 0 && m < n1 && nums2[mlen - m - 1] > nums1[m])
                begin = m + 1;
            else if(m > 0 && mlen - m < n2 && nums1[m - 1] > nums2[mlen - m])
                end = m - 1;
            else{
                if(m == 0)
                    lmax = nums2[mlen - 1];
                else if(m == mlen)
                    lmax = nums1[mlen - 1];
                else
                    lmax = max(nums1[m - 1], nums2[mlen - m - 1]);
                if((n1 + n2) & 1)
                    return lmax;
                
                if(m == n1)
                    rmin = nums2[mlen - m];
                else if(mlen - m == n2)
                    rmin = nums1[m];
                else
                    rmin = min(nums1[m], nums2[mlen - m]);
                return (lmax + rmin) / 2.0;
            }
        }
        return 0;
    };
};
