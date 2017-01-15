/*
There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1]

4, [[1,0],[2,0],[3,1],[3,2]]
There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is[0,2,1,3].

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
*/


class Solution {
public:
    bool DFS(int n, vector<int>&in, vector<int>&visited, vector<pair<int, int>>& prerequisites, vector<int>&res){
        if(visited[n] == 1)
            return false;
        if(visited[n] == 2)
            return true;
        visited[n] = 1;
        for(int i = 0;i < prerequisites.size(); ++ i){
            if(prerequisites[i].second != n)
                continue;
            if(!DFS(prerequisites[i].first, in, visited, prerequisites, res))
                return false;
        }
        visited[n] = 2;
        res.push_back(n);
        return true;
    }
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<int> in(numCourses, 0);
        vector<int> visited(numCourses, 0);
        vector<int> res;
        for(int i = 0;i < prerequisites.size(); ++ i){
            ++ in[prerequisites[i].first] ;
        }
        for(int i = 0;i < numCourses; ++ i){
            if(!in[i] && !DFS(i, in, visited, prerequisites, res))
                return vector<int>(0);
        }
        for(int i = 0;i < visited.size(); ++ i)
            if(!visited[i])
                return vector<int>(0);
        reverse(res.begin(), res.end());
        return res;
    }
};
