/*
Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
update(3, 2, 2)
sumRegion(2, 1, 4, 3) -> 10
Note:
The matrix is only modifiable by the update function.
You may assume the number of calls to update and sumRegion function is distributed evenly.
You may assume that row1 ≤ row2 and col1 ≤ col2.
*/

class SegmentTreeNode {
public:
    int xul, yul, xbr, ybr, val;
    SegmentTreeNode *leftup, *rightup, *leftdown, *rightdown;
    SegmentTreeNode(int _xul, int _yul, int _xbr, int _ybr, int v, SegmentTreeNode *lu, SegmentTreeNode *ru, SegmentTreeNode *ld, SegmentTreeNode *rd): xul(_xul), yul(_yul), xbr(_xbr), ybr(_ybr), val(v), leftup(lu), rightup(ru), leftdown(ld), rightdown(rd){};
};
class SegmentTree {
public:
    SegmentTreeNode *root;
    SegmentTree(vector<vector<int>> &matrix){
        if(!matrix.empty())
            root = BuildSegmentTree(matrix, 0, 0, matrix.size() - 1, matrix[0].size() - 1);
    }
    SegmentTreeNode *BuildSegmentTree(vector<vector<int>> &matrix, int sx, int sy, int ex, int ey){
        if(sx > ex || sy > ey) return NULL;
        if(sx == ex && sy == ey) return new SegmentTreeNode(sx, sy, ex, ey, matrix[sx][sy], NULL, NULL, NULL, NULL);
        int mx = sx + ((ex - sx) >> 1), my = sy + ((ey - sy) >> 1);
        SegmentTreeNode *lu, *ld, *ru, *rd;
        lu = BuildSegmentTree(matrix, sx, sy, mx, my);
        ld = BuildSegmentTree(matrix, mx + 1, sy, ex, my);
        ru = BuildSegmentTree(matrix, sx, my + 1, mx, ey);
        rd = BuildSegmentTree(matrix, mx + 1, my + 1, ex, ey);
        return new SegmentTreeNode(sx, sy, ex, ey, (lu ? lu->val : 0) + (ld ? ld->val : 0) + (ru ? ru->val : 0) + (rd ? rd->val : 0), lu, ld, ru, rd);
    }
    void update(int x, int y, int val){
        update(root, x, y, val);
    }
    int update(SegmentTreeNode *node, int x, int y, int val){
        if(!node) return 0;
        if(node->xul > x || node->yul > y || node->xbr < x || node->ybr < y) return node->val;
        if(node->xul == node->xbr && node->xbr == x && node->yul == node->ybr && node->ybr == y)
            return node->val = val;
        return node->val = update(node->leftup, x, y, val) + update(node->rightup, x, y, val) + update(node->leftdown, x, y, val) + update(node->rightdown, x, y, val);
    }
    int sumRegion(int sx, int sy, int ex, int ey){
        return sumRegion(root, sx, sy, ex, ey);
    }
    int sumRegion(SegmentTreeNode* node, int sx, int sy, int ex, int ey){
        if(!node || node->xbr < sx || node->ybr < sy || node->xul > ex || node->yul > ey) return 0;
        if(node->xul >= sx && node->yul >= sy && node->xbr <= ex && node->ybr <= ey) return node->val;
        return sumRegion(node->leftup, sx, sy, ex, ey) + sumRegion(node->leftdown, sx, sy, ex, ey) + sumRegion(node->rightup, sx, sy, ex, ey) + sumRegion(node->rightdown, sx, sy, ex, ey);
    }
};
class NumMatrix {
public:
    SegmentTree *tree;
    NumMatrix(vector<vector<int>> &matrix) {
        tree = new SegmentTree(matrix);
    }

    void update(int row, int col, int val) {
        tree->update(row, col, val);
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return tree->sumRegion(row1, col1, row2, col2);
    }
};


// Your NumMatrix object will be instantiated and called as such:
// NumMatrix numMatrix(matrix);
// numMatrix.sumRegion(0, 1, 2, 3);
// numMatrix.update(1, 1, 10);
// numMatrix.sumRegion(1, 2, 3, 4);
