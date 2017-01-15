/*
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line
*/

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    int maxPoints(vector<Point>& points) {
        map<pair<string, string>, unordered_set<Point*>> mp;
        int n = points.size();
        double k = 0, b = 0;
        char kk[20], bb[20];
        string kkk, bbb;
        for(int i = 0;i < n; ++ i)
            for(int j = i + 1; j < n; ++ j){
                if(points[i].x == points[j].x)
                    k = INT_MIN, b = points[j].x;
                else{
                    k = (double)(points[j].y - points[i].y) / (points[j].x - points[i].x);
                    b = points[i].y - points[i].x * k;
                }
                sprintf(kk, "%.8lf", k);
                sprintf(bb, "%.8lf", b);  //由于精度问题，保留8位小数
                kkk = kk;
                bbb = bb;
                if(mp.find(pair<string, string>(kkk,bbb)) == mp.end()){
                    unordered_set<Point*> u;
                    mp[pair<string,string>(kkk,bbb)] = u;
                }
                mp[pair<string,string>(kkk,bbb)].insert(&points[i]);
                mp[pair<string,string>(kkk,bbb)].insert(&points[j]);
            }
        int res = points.size() > 0;
        for(auto iter = mp.begin(); iter != mp.end(); ++ iter){
            res = max(res, (int)((iter->second).size()));
        }
        return res;
    }
};
