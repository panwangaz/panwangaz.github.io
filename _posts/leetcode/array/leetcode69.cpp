#include<iostream>
using namespace std;


class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) return 0;
        float ans = x / 2.0;
        float pre_ans = 0;
        while (abs(ans - pre_ans) > 1e-2) {
            pre_ans = ans;
            ans = (ans + x / ans) / 2;
        }
        return (int) ans;
    }
};

int main() {
    Solution solver = Solution();
    int ans = solver.mySqrt(1);
    return 0;
}
