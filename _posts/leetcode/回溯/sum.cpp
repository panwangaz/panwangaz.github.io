#include <iostream>
#include <vector>
using namespace std;

bool hasSumHelper(vector<int>& nums, int target, int cur_sum, int idx) {
    if (cur_sum == target) {
        return true;
    }
    if (cur_sum > target || idx == nums.size()) {
        return false;
    }
    return hasSumHelper(nums, target, cur_sum + nums[idx], idx+1) ||
           hasSumHelper(nums, target, cur_sum, idx+1);
}

bool hasSum(vector<int>& nums, int target) {
    return hasSumHelper(nums, target, 0, 0);
}

int main() {
    vector<int> nums = {1, 4, 2, 7, 5};
    int target = 20;
    bool has_sum = hasSum(nums, target);
    cout << has_sum << endl; // output: 1 (表示存在若干个数的和为 11)
    return 0;
}
