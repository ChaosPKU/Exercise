
/*
 MaxSliceSwap
 A non-empty zero-indexed array A consisting of N integers is given. A pair of integers (P, Q), such that 0 ≤ P ≤ Q < N, is called a slice of array A. The sum of a slice (P, Q) is the total of A[P] + A[P+1] + ... + A[Q]. The maximum sum is the maximum sum of any slice of A.
 
 For example, consider array A such that:
 
 A[0] = 3
 A[1] = 2
 A[2] = -6
 A[3] = 3
 A[4] = 1
 For example (0, 1) is a slice of A that has sum A[0] + A[1] = 5. This is the maximum sum of A.
 
 You can perform a single swap operation in array A. This operation takes two indices I and J, such that 0 ≤ I ≤ J < N, and exchanges the values of A[I] and A[J]. The goal is to find the maximum sum you can achieve after performing a single swap.
 
 For example, after swapping elements 2 and 4, you will get the following array A:
 
 A[0] = 3
 A[1] = 2
 A[2] = 1
 A[3] = 3
 A[4] = -6
 After that, (0, 3) is a slice of A that has the sum A[0] + A[1] + A[2] + A[3] = 9. This is the maximum possible sum of A after a single swap.
 
 Write a function:
 
 int solution(vector<int> &A);
 that, given a non-empty zero-indexed array A of N integers, returns the maximum possible sum of any slice of A after a single swap operation.
 
 For example, given:
 
 A[0] = 3
 A[1] = 2
 A[2] = -6
 A[3] = 3
 A[4] = 1
 the function should return 9, as explained above.
 
 Assume that:
 
 N is an integer within the range [1..100,000];
 each element of array A is an integer within the range [−10,000..10,000].
 Complexity:
 
 expected worst-case time complexity is O(N);
 expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).
 Elements of input arrays can be modified.
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int help(vector<int> &a) {
    int n = a.size();
    vector<int> f,g,h;
    f.resize(n);
    f[0] = a[0];
    int now = a[0];
    for (int i = 1; i < n; ++i) {
        now = max(now, a[i]);
        f[i] = max(a[i] + f[i - 1], now); //f[i]--只允许交换一次,且只允许与i之前位置的数字交换，以位置i为结尾的最大连续子数组的和;且交换数字必定位于最大连续子数组的起始位置;
    }
    g.resize(n);
    g[n - 1] = a[n - 1];
    int answer = a[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        g[i] = max(g[i + 1], 0) + a[i]; //g[i]--不交换，以i为起始位置的最大连续子数组的和；
        answer = max(answer, g[i]);
    }
    h.resize(n);
    for (int i = 1; i < n; ++i) {
        h[i] = answer = max(answer, g[i] - a[i] + f[i - 1]);
    }
    return answer;
}

int solution(vector<int> &A) {
    // write your code in C++11
    int answer = help(A);
    for (int i = 0, j = A.size() - 1; i < j; ++i,--j) {
        swap(A[i],A[j]);
    }
    answer = max(answer,help(A));
    return answer;
}

int main(){
    vector<int> v({10, -10000, 3, 2, -6, 3, 1});
    cout << solution(v) << endl;
}
