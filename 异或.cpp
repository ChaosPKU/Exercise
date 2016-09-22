#include "MyHeader.h"

//题目:给定整数m以及n个数字A1,A2,...,An,将数列A中所有元素两两异或，共能得到n(n-1)/2个结果。请求出这些结果中大于m的有多少个。
//基本思路是对二进制的每一位进行考虑，每次将数组按这一位是0和1分成两组A和B.如果m的当前位是1,那么只需考虑A和B互相异或，A内部异或与B内部异或一定比m小;如果m的当前位是0,那么A和B互相异或一定符合要求，只需考虑A内部异或和B内部异或。需要进一步考虑的按照下一位继续划分直到分完为止或已经得出结果。复杂度是O(nlogn)

void split(const vector<int> &nums, vector<int> &nums0, vector<int> &nums1, int len){
    //将nums按二进制第len位是0还是1，分成两个vector
    for(int num : nums){
        if((num >> (len - 1)) & 1)
            nums1.push_back(num);
        else
            nums0.push_back(num);
    }
}

int solve(const vector<int> &nums, int len, const int &m);
int solve(const vector<int> &nums0, const vector<int> &nums1, int len, const int &m){
    //在nums0和nums1之中分别找两个数，其异或后二进制的第len位大于等于m的第len位
    if(nums0.empty() || nums1.empty()) return 0;
    if(!len) return 0;
    
    vector<int> nums00, nums01, nums10, nums11;
    split(nums0, nums00, nums01, len);
    split(nums1, nums10, nums11, len);
    
    if((m >> (len - 1)) & 1)
        return solve(nums10, nums01, len - 1, m) + solve(nums11, nums00, len - 1, m);
    else
        return solve(nums00, nums10, len - 1, m) + solve(nums01, nums11, len - 1, m) + (int)(nums00.size() * nums11.size() + nums10.size() * nums01.size());
}

int solve(const vector<int> &nums, int len, const int &m){
    //在nums中找成对的两个数，其异或后二进制第len位大于等于m的
    if(nums.empty() || !len) return 0;
    vector<int> nums0, nums1;
    split(nums, nums0, nums1, len);
    if((m >> (len - 1)) & 1)
        return solve(nums0, nums1, len - 1, m);
    else
        return (int)(nums0.size() * nums1.size()) + solve(nums0, len - 1, m) + solve(nums1, len - 1, m);
}

int advanced(vector<int> nums, int m){
    int maxN = 0;
    for(int i = 0;i < nums.size(); ++ i)
        maxN = max(maxN, nums[i]);
    int len = (ceil)(log2(maxN));
    return solve(nums, len, m);
}

int naive(vector<int> nums, int m){
    int res = 0;
    for(int i = 0;i < nums.size(); ++ i)
        for(int j = i + 1; j < nums.size(); ++ j)
            res += ((nums[i] ^ nums[j]) > m);
    return res;
}

int main(){
    int n, m;
    while(scanf("%d%d", &n, &m)){
        vector<int> nums(n, 0);
        for(int i = 0; i < n; ++ i)
            nums[i] = rand()%100000000000 + 1;
        cout << advanced(nums, m) << " " <<  naive(nums, m) << endl;
        //随机生成数据验证
    }
    return 0;
}
