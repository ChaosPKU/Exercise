/*
Given an integer array, sort it in ascending order.
Example
Given [3, 2, 1, 4, 5], return [1, 2, 3, 4, 5].
*/

// Swap Sort
class Solution {
public:
    void sortIntegers(vector<int>& A) {
        for(int i = 0;i < A.size(); ++ i)
            for(int j = i + 1; j < A.size(); ++ j){
                if(A[j] < A[i])
                    swap(A[j], A[i]);
            }
    }
};

// Insert Sort
class Solution {
public:
    void sortIntegers(vector<int>& A) {
        for(int i = 0;i < (int)A.size() - 1; ++ i){
            int j = i + 1, tmp = A[j];
            while(j > 0 && A[j - 1] > tmp) {
                A[j] = A[j - 1];
                -- j;
            }
            A[j] = tmp;
        }
    }
};

// Bubble Sort
class Solution {
public:
    void sortIntegers(vector<int>& A) {
        int n = A.size();
        for(int i = 0;i < n - 1; ++ i){
            for(int j = 0;j < n - 1 - i; ++ j)
                if(A[j] > A[j + 1])
                    swap(A[j], A[j + 1]);
        }
    }
};

// Merge Sort

// Quick Sort

// Heap Sort
