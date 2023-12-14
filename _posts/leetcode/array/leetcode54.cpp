class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int row = matrix.size(), col = matrix[0].size();
        vector<int> res(row * col, 0);
        int up = 0, down = row - 1;
        int left = 0, right = col - 1;
        while (res.size() < row * col) {
            for (int i = left; i <= right; i++) {
                res.push_back(matrix[up][i]);
            }
            up++;
            for (int j = up; j <= down; j++) {
                res.push_back(matrix[j][right]);
            }
            right--;
            for (int i = right; i >= left; i--) {
                res.push_back(matrix[down][i]);
            }
            down--;
            for (int i = down; i >= up; i--) {
                res.push_back(matrix[i][left]);
            }
            left++;
        }
        return res;
    }
};
