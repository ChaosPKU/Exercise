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
class Solution {
public:
    void merge(vector<int>& A, int b, int m, int e){
        vector<int> B(e - b + 1, 0);
        int i = b, j = m + 1, k = 0;
        while(i <= m && j <= e){
            if(A[i] <= A[j])
                B[k ++] = A[i ++];
            else
                B[k ++] = A[j ++];
        }
        while(i <= m) B[k ++] = A[i ++];
        while(j <= e) B[k ++] = A[j ++];
        for(i = 0;i <= e - b; ++ i)
            A[b + i] = B[i];
    }
    void mergesort(vector<int>& A, int b, int e){
        if(b < e){
            int m = b + ((e - b) >> 1);
            mergesort(A, b, m);
            mergesort(A, m + 1, e);
            merge(A, b, m, e);
        }
    }
    void sortIntegers(vector<int>& A) {
        mergesort(A, 0, A.size() - 1);
    }
};

// Quick Sort
class Solution {
public:
    void quicksort(vector<int>& A, int b, int e){
        if(b >= e) return;
        if(e - b == 1){
            if(A[b] > A[e]) swap(A[b], A[e]);
            return;
        }
        int idx = (rand() % (e - b + 1)) + b, pivot = A[idx], pb = b, pe = e;
        swap(A[idx], A[b]);
        while(b < e){
            while(b < e && A[e] >= pivot) -- e;
            A[b] = A[e];
            while(b < e && A[b] <= pivot) ++ b;
            A[e] = A[b];
        }
        A[b] = pivot;
        quicksort(A, pb, b - 1);
        quicksort(A, b + 1, pe);
    }
    void sortIntegers(vector<int>& A) {
        quicksort(A, 0, A.size() - 1);
    }
};
// Heap Sort
class Solution {
public:
    template<typename T>
    void MinHeapify(vector<T>& arry, int size, int element)
    {
        int lchild = element * 2 + 1, rchild = lchild + 1;//左右子树
        while(rchild < size)//子树均在范围内
        {
            if(arry[element] >= arry[lchild] && arry[element] >= arry[rchild])//如果比左右子树都小，完成整理
                return;
            if(arry[lchild] >= arry[rchild]){//如果左边最小
                swap(arry[element], arry[lchild]);//把左面的提到上面
                element = lchild;//循环时整理子树
            }
            else{//否则右面最小
                swap(arry[element], arry[rchild]);//同理
                element = rchild;
            }
            lchild = element * 2 + 1;
            rchild = lchild + 1;//重新计算子树位置
        }
        if(lchild < size && arry[lchild] > arry[element]){//只有左子树且子树小于自己
            swap(arry[lchild], arry[element]);
        }
        return;
    }
    //堆排序time:O(nlgn)
    template<typename T>
    void HeapSort(vector<T>& arry, int size)
    {
        for(int i = size - 1; i >= 0; i--)//从子树开始整理树
            MinHeapify(arry, size, i);
        while(size > 0){//拆除树
            swap(arry[size - 1], arry[0]);//将根（最小）与数组最末交换
            size --;//树大小减小
            MinHeapify(arry, size, 0);//整理树
        }
        return;
    }
    void sortIntegers(vector<int>& A) {
        HeapSort(A, (int)A.size());
    }
};

// Radix Sort
class Solution {
public:
    int NumOfDigits(vector<int>& A){
        int largest = 0;
        for(int num : A)
            largest = largest < num ? num : largest;
        int digits = 0;
        while(largest){
            digits ++ ;
            largest /= 10;
        }
        return digits;
    }
    void DistributeElements(vector<int>& A, vector<vector<int>>& B, int digits){
        int divisor = 1;
        for(int i = 0;i < digits; ++ i)
            divisor *= 10;
        for(int i = 0;i < A.size(); ++ i){
            int num = (A[i] % divisor - A[i] % (divisor / 10)) / (divisor / 10);
            B[num].push_back(A[i]);
        }
    }
    void CollectElements(vector<int>& A, vector<vector<int>>& B){
        int k = 0;
        for(int i = 0;i < 10; ++ i)
            for(int j = 0;j < B[i].size(); ++ j)
                A[k ++] = B[i][j];
    }
    void RadixSort(vector<int>& A){
        int digits = NumOfDigits(A);
        for(int i = 1;i <= digits; ++ i){
            vector<vector<int>> B(10);
            DistributeElements(A, B, i);
            CollectElements(A, B);
        }
    }
    void sortIntegers(vector<int>& A) {
        RadixSort(A);
    }
};
