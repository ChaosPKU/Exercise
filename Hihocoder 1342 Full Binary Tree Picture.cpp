/*
描述
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
#include <cmath>
using namespace std;

struct TreeNode{
    int x, y;
    TreeNode *left, *right;
    TreeNode(int _x, int _y): x(_x), y(_y){
        left = right = NULL;
    }
};

int calc_height(int height){
    if(height <= 3) return height - 1;
    else return calc_height(height - 1) * 2 + 1;
}

void build(TreeNode* node, int height){
    if(height == 1) return ;
    int len = calc_height(height) + 1;
    node->left = new TreeNode(node->x + len, node->y - len);
    node->right = new TreeNode(node->x + len, node->y + len);
    build(node->left, height - 1);
    build(node->right, height - 1);
}

int count(TreeNode* node, int x1, int y1, int x2, int y2){
    return node ? ((node->x >= x1 && node->y >= y1 && node->x <= x2 && node->y <= y2) + count(node->left, x1, y1, x2, y2) + count(node->right, x1, y1, x2, y2)) : 0;
}

int main(){
    int N, M;
    cin >> N >> M;
    TreeNode *root = new TreeNode(0, 0);
    build(root, N);
    int x1, y1, x2, y2;
    while(M --){
        cin >> x1 >> y1 >> x2 >> y2;
        cout << count(root, x1, y1, x2, y2) << endl;
    }
    return 0;
}
