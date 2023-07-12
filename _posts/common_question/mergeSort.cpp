#include<vector>
using namespace std;

void merge(vector<int>& nums, int left, int right, vector<int>& ans) {
    if (left >= right) return;
    int mid = (right - left) / 2 + left;
    int i = left, j = mid + 1;
    int k = 0;
    while (i <= mid && j <= right) {
        if (nums[i] < nums[j]) {
            ans[k++] = nums[i++];
        }
        else ans[k++] = nums[j++];
    }
    if (i <= mid) {
        ans[k++] = nums[i++];
    }
    if (j <= right) {
        ans[k++] = nums[j++];
    }
    for (int i = left; i <= right; i++) {
        nums[i] = ans[i - left];
    }
    return;
}

void mergeSort(vector<int>& nums, int left, int right, vector<int>& ans) {
    if (left >= right) return;
    int mid = (right - left) / 2 + left;
    mergeSort(nums, left, mid, ans);
    mergeSort(nums, mid + 1, right, ans);
    merge(nums, left, right, ans);
    return;
}

int main() {
    vector<int> num{4, 2, 1, 5, 4};
    vector<int> ans(num);
    mergeSort(num, 0, num.size() - 1, ans);
    return 0;
}
