#include<vector>
#include<iostream>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        int row = matrix.size(), col = matrix[0].size();
        int startX = 0, startY = 0;
        int offset = 1;
        while (res.size() < row * col) {
            int i = startX, j = startY;
            for (j = startY; j < col - offset; j++) {
                res.push_back(matrix[startX][j]);
            }
            for (i = startX; i < row - offset; i++) {
                res.push_back(matrix[i][j]);
            }
            for (; j > startY; j--) {
                res.push_back(matrix[i][j]);
            }
            for (; i > startX; i--) {
                res.push_back(matrix[i][j]);
            }
            startX++;
            startY++;
            offset++;
        }
        return res;
    }
};

int main() {
    Solution solver = Solution();
    vector<vector<int>> data{{1,2,3},{4,5,6},{7,8,9}};
    vector<int> res = solver.spiralOrder(data);
    return 0;
}