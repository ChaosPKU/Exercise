/*
Recently Little Hi joined an algorithm learning group. The group consists of one algorithm master and N members. The members are numbered from 1 to N. Each member has one or more other members as his mentors. Some members' mentor is the master himself.

Every week each member sends a report of his own learning progress and the reports collected from his pupils (if there is any) to his mentors. The group is so well designed that there is no loop in the reporting chain so no one receives his own report from his pupil. And finally the master gets every one's report (maybe more than once).

Little Hi notices that for some members their reporting routes to the master can be easily cut off by a single member's (other than the master and himself) absence from the reporting duty. They are called unstable members while the others are stable members. Given the reporting network of the group, can you find out how many members are stable?

Assume there are 4 members in the group. Member 1 and 2 both have the master as their only mentor. Member 3 has 2 mentors: member 1 and member 2. Member 4 has 1 mentor: member 3. Then member 4 is the only unstable member in the group because if member 3 is absent his learning report will be unable to be sent to the master. 

输入
The first line contains an integer N, the number of members.

The i-th line of the following N lines describe the mentors of the i-th member. The first integer is Ki, the number of mentors of the i-th member. Then follows Ki integers A1 ... AN, which are his mentors' numbers. Number 0 indicates that the master is one of his mentor.

For 40% of the data, 1 ≤ N ≤ 1000.

For 100% of the data, 1 ≤ N ≤ 100000.

For 100% of the data, 1 ≤ Ki ≤ 10, Ki < N, 0 ≤ Ai ≤ N. 

输出
Output the number of stable members.

样例输入
5
1 0
1 0
2 1 2
1 3
2 4 3 
样例输出
3
*/
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

unordered_set<int> udst[100005];
vector<int> nums(100005, 0), msg(100005, 0); // nums表示当前节点的父节点个数, msg代表已接收消息数

void calc(vector<vector<int>> &lnklst, int &res, int i){
    int state = i;
    if(udst[i].size() == 1 && *udst[i].begin())  // state表示当前节点到根结点路径上第一个稳定节点
        state = *udst[i].begin();
    else if(i) res ++;
    for(int p : lnklst[i]){
        udst[p].insert(state);
        if(++ msg[p] == nums[p]) //子节点p已经获得了所有父节点信息
            calc(lnklst, res, p);
    }
}

int main(){
    int N, K, A, res = 0;
    cin >> N;
    vector<vector<int>> lnklst(N + 1);
    for(int i = 1;i <= N; ++ i){
        cin >> K;
        while(K --){
            cin >> A;
            lnklst[A].push_back(i);
            nums[i] ++;
        }
    }
    calc(lnklst, res, 0);
    cout << res << endl;
    return 0;
}
