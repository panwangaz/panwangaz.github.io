#include<vector>
#include<iostream>
using namespace std;

int findLeft(vector<int>& data, int target) {
    int left = 0, right = data.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (data[mid] == target) right = mid - 1;
        else if (data[mid] > target) right = mid - 1;
        else if (data[mid] < target) left = mid + 1;
    }
    return left;
}

int findRight(vector<int>& data, int target) {
    int left = 0, right = data.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (data[mid] == target) left = mid + 1;
        else if (data[mid] > target) right = mid - 1;
        else if (data[mid] < target) left = mid + 1;
    }
    return left - 1;
}

int main() {
    vector<int> num{0, 1, 2, 2, 2, 3, 4, 5};
    int target = 2;
    int left = findLeft(num, target);
    int right = findRight(num, target);
    cout << "the found value: " << target << " left: " << left << " right: " << right << endl;
    return 0;
}
