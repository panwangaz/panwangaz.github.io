#include<vector>
#include<iostream>
#include<limits.h>
using namespace std;

class Solution {
public:

    int traverse(vector<vector<int>>& matrix, vector<vector<int>>& memo, int i, int j, int val) {
        int row = matrix.size(), col = matrix[0].size();
        if (i < 0 || i >= row || j < 0 || j >= col) return 0;
        if (memo[i][j] != 0) return memo[i][j];
        memo[i][j] = val;
        if (i + 1 < row && matrix[i+1][j] > matrix[i][j]) memo[i][j] = max(memo[i][j], traverse(matrix, memo, i + 1, j, val + 1));
        if (i - 1 >= 0 && matrix[i-1][j] > matrix[i][j]) memo[i][j] = max(memo[i][j], traverse(matrix, memo, i - 1, j, val + 1));
        if (j + 1 < col && matrix[i][j+1] > matrix[i][j]) memo[i][j] = max(memo[i][j], traverse(matrix, memo, i, j + 1, val + 1));
        if (j - 1 >= 0 && matrix[i][j-1] > matrix[i][j]) memo[i][j] = max(memo[i][j], traverse(matrix, memo, i, j - 1, val + 1));
        return memo[i][j];
    }

    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int row = matrix.size(), col = matrix[0].size();
        vector<vector<int>> memo(row, vector<int>(col, 0));
        int res = INT_MIN;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                int val = traverse(matrix, memo, i, j, 1);
                res = max(res, val);
            }
        }
        return res;
    }
};


int main() {
    Solution solver = Solution();
    vector<vector<int>> data{{9,9,4},{6,6,8},{2,1,1}};
    int res = solver.longestIncreasingPath(data);
    cout << "ans: " << res << endl;
    return 0;
}
