/*
Description

There are several ancient Greek texts that contain descriptions of the fabled island Atlantis. Some of these texts even include maps of parts of the island. But unfortunately, these maps describe different regions of Atlantis. Your friend Bill has to know the total area for which maps exist. You (unwisely) volunteered to write a program that calculates this quantity.
Input

The input consists of several test cases. Each test case starts with a line containing a single integer n (1 <= n <= 100) of available maps. The n following lines describe one map each. Each of these lines contains four numbers x1;y1;x2;y2 (0 <= x1 < x2 <= 100000;0 <= y1 < y2 <= 100000), not necessarily integers. The values (x1; y1) and (x2;y2) are the coordinates of the top-left resp. bottom-right corner of the mapped area. 
The input file is terminated by a line containing a single 0. Don't process it.
Output

For each test case, your program should output one section. The first line of each section must be "Test case #k", where k is the number of the test case (starting with 1). The second one must be "Total explored area: a", where a is the total explored area (i.e. the area of the union of all rectangles in this test case), printed exact to two digits to the right of the decimal point. 
Output a blank line after each test case.
Sample Input

2
10 10 20 20
15 15 25 25.5
0
Sample Output

Test case #1
Total explored area: 180.00 
*/
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 205

struct SegmentTreeNode{
    int l, r, c;    //l, r 线段树的左右端点index值,c记录重叠情况
    double cnt, lf, rf;     //lf, rf左右的真实端点值,cnt记录总长度
    SegmentTreeNode *left, *right;
    SegmentTreeNode(int _l, int _r, double _lf, double _rf): l(_l), r(_r), lf(_lf), rf(_rf){
        c = cnt = 0;
        left = right = NULL;
    }
};

struct Line{
    double x, y1, y2;   //定义一个平行于y轴的线段
    int f;  //标记出边还是入边
    void set(double _x, double _y1, double _y2, int _f){
        x = _x;
        y1 = _y1;
        y2 = _y2;
        f = _f;
    }
}lines[MAXN];

bool cmp(const Line &a, const Line &b){
    return a.x < b.x;
}

double y[MAXN];

struct SegmentTree{
    SegmentTreeNode *root;
    SegmentTree(int l, int r){
        root = build(l, r);
    }
    SegmentTreeNode* build(int l, int r){
        if(l > r) return NULL;
        SegmentTreeNode *node = new SegmentTreeNode(l, r, y[l], y[r]);
        if(l == r - 1) return node;
        int m = (l + r) >> 1;
        SegmentTreeNode *left = build(l, m), *right = build(m, r);
        node->left = left;
        node->right = right;
        return node;
    }
    void update(Line l){
        update(root, l);
    }
    double update(SegmentTreeNode *node, Line l){
        if(!node) return 0;
        if(l.y1 >= node->rf || l.y2 <= node->lf) return node->cnt;
        if(l.y1 <= node->lf && l.y2 >= node->rf && node->l + 1 == node->r){
            node->c += l.f;
            node->cnt = node->c ? node->rf - node->lf : 0;
            return node->cnt;
        }
        return node->cnt = update(node->left, l) + update(node->right, l);
    }
    double query(){
        return root->cnt;
    }
};

int main(){
    int N;
    int i = 0, t = 0, cnt = 0;
    double x1, y1, x2, y2;
    while(scanf("%d", &N), N){
        ++ cnt;
        t = 1;
        for(int i = 0; i < N; ++ i){
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            lines[t].set(x1, y1, y2, 1);
            y[t] = y1;
            ++ t;
            lines[t].set(x2, y1, y2, -1);
            y[t] = y2;
            ++ t;
        }
        sort(lines + 1, lines + t, cmp);
        sort(y + 1, y + t);
        
        double res = 0;
        SegmentTree *st = new SegmentTree(1, t - 1);
        st->update(lines[1]);
        for(i = 2; i < t; ++ i){
            res += st->query() * (lines[i].x - lines[i - 1].x);
            st->update(lines[i]);
        }
        printf("Test case #%d\nTotal explored area: %.2f\n\n", cnt, res);
    }
    return 0;
}
