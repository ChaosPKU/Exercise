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
