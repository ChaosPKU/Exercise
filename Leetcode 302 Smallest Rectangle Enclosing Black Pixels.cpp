/*

An image is represented by a binary matrix with 0 as a white pixel and 1 as a black pixel. The black pixels are connected, i.e., there is only one black region. Pixels are connected horizontally and vertically. Given the location (x, y) of one of the black pixels, return the area of the smallest (axis-aligned) rectangle that encloses all black pixels.

For example, given the following image:

[
  "0010",
  "0110",
  "0100"
]
and x = 0, y = 2,
Return 6.

*/

class Solution {
public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        if(image.empty()) return 0;
        int n = (int)image.size(), m = (int)image[0].size();
        int top = 0, bottom = 0, left = 0, right = 0;
        top = search(image, 0, x, 0, m, true, true);
        bottom = search(image, x + 1, n, 0, m, false, true);
        left = search(image, 0, y, top, bottom, true, false);
        right = search(image, y + 1, m, top, bottom, false, false);
        return (bottom - top) * (right - left);
    }
    bool isWhite(vector<vector<char>>& image, int mid, int k, bool isRow){
        return ((isRow) ? image[mid][k]: image[k][mid]) == '0';
    }
    int search(vector<vector<char>>& image, int i, int j, int low, int high, bool opt, bool isRow){
        while(i < j){
            int k = low, mid = i + ((j - i) >> 1);
            while(k < high && isWhite(image, mid, k, isRow)) ++ k;
            if(k < high == opt)  //opt决定二分方向
                j = mid;
            else i = mid + 1;
        }
        return i;
    }
};
