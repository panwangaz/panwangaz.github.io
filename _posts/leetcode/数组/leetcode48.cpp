#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int row = matrix.size(), col = matrix[0].size();
        for (int i = 0; i < row / 2; i++) {
            for (int j = 0; j < col; j++) {
                swap(matrix[i][j], matrix[row - i - 1][j]);
            }
        }
        for (int i = 0; i < row; i++) {
            for (int j = i + 1; j < col; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        return;

    }
};

int main() {
    vector<vector<int>> data = {{1,2,3},{4,5,6},{7,8,9}};
    Solution solver = Solution();
    solver.rotate(data);
    return 0;
}
