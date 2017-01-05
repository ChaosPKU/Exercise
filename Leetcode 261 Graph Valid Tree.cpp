/*
Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.

For example:

Given n = 5 and edges = [[0, 1], [0, 2], [0, 3], [1, 4]], return true.

Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]], return false.

Hint:

Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], what should your return? Is this case a valid tree?
According to the definition of tree on Wikipedia: “a tree is an undirected graph in which any two vertices are connected by exactly one path. In other words, any connected graph without simple cycles is a tree.”
Note: you can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.
*/

// 并查集判定图是否为树，检查边数条件之后，主要是判环，如果一个新的边的两个节点在一个集合中，则存在环。
class Solution {
public:
    bool validTree(int n, vector<pair<int, int>>& edges) {
        if(n - 1 != edges.size()) return false;
        vector<int> prt(n, -1), rak(n, 1);
        for(int i = 0;i < n; ++ i)
            prt[i] = i;
        for(int i = 0;i < n - 1; ++ i){
            int x = edges[i].first, y = edges[i].second;
            if(!myUnion(x, y, prt, rak)) return false;
        }
        return true;
    }
    int myFind(int x, vector<int> &prt){
        if(x == prt[x]) return x;
        return prt[x] = myFind(prt[x], prt);
    }
    bool myUnion(int x, int y, vector<int> &prt, vector<int> &rak){
        int xx = myFind(x, prt), yy = myFind(y, prt);
        if(xx == yy) return false;
        if(rak[xx] >= rak[yy]){
            prt[yy] = xx;
            rak[xx] += rak[yy];
        }
        else{
            prt[xx] = yy;
            rak[yy] += rak[xx];
        }
        return true;
    }
};
