#include<vector>
#include<iostream>
#include<cmath>
using namespace std;


class Solution {
public:
    float mySqrt(float x) {
        if (x <= 0) {
            throw runtime_error("Dived by zero!");
        }

        float low = 0;
        float high = x;
        float mid;
        if (x < 1) high = 1;
        while (high - low > 1e-3) {
            mid = (low + high) / 2;
            if (mid * mid > x) {
                high = mid;
            } else {
                low = mid;
            }
        }

        return low;
    }

    float newton(float x) {
        float x1 = x;
        while (abs(x1 * x1 - x) > 1e-3) {
            x1 = (x1 + x / x1) / 2.0;
        }
        return x1;
    }
};

int main() {
    Solution solver = Solution();
    float data = 1.9;
    // cin >> data;
    float res = solver.mySqrt(data);
    float ans = solver.newton(data);
    cout << "the sqrt of " << data << " is " << res << " newton: " << ans << endl;
    return 0;
}
