#include<vector>
#include<iostream>
using namespace std;

extern void print_vector(vector<int>& data);

class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> res;
        int left = 1, right = 1;
        int window = 0;
        while (right <= target) {
            window += right;
            right++;
            if (window >= target) {
                if (window == target) {
                    vector<int> tmp;
                    for(int i = left; i < right; i++) {
                        tmp.push_back(i);
                    }
                    print_vector(tmp);
                    res.push_back(tmp);
                }
                while (window >= target) {
                    window -= left;
                    left++;
                }
            }
        }
        return res;
    }
};

int main() {
    int input = 15;
    Solution solver = Solution();
    vector<vector<int>> val = solver.findContinuousSequence(input);
    cout << "input is: " << input << endl;
    cout << "output is: " << val.size() << endl;
    return 0;
}
