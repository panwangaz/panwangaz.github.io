#include<vector>
using namespace std;


class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int val = 1;
        int loop = n / 2;
        int i = 0;
        vector<vector<int>> res(n, vector<int>(n, 0));
        int row = 0, col = 0;
        int offset = 1;
        while (i < loop) {
            while (col < n - offset) {
                res[row][col] = val;
                val++;
                col++;
            }

            while (row < n - offset) {
                res[row][col] = val;
                val++;
                row++;
            }

            while (col >= offset) {
                res[row][col] = val;
                val++;
                col--;
            }

            while (row >= offset) {
                res[row][col] = val;
                val++;
                row--;
            }
            i++;
            offset++;
            row++;
            col++;
        }
        if (n % 2 == 1) res[n / 2][n / 2] = n * n;
        return res;
    }
};

int main() {
    Solution solver = Solution();
    vector<vector<int>> res = solver.generateMatrix(4);
    return 0;
}
