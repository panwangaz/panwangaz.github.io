#include<vector>
#include<stdlib.h>
#include<iostream>
using namespace std;

int partition(vector<int>& num, int left, int right) {
    int tmp = std::rand()%(right - left + 1) + left;
    swap(num[tmp], num[left]);
    int pivort = num[left];
    while (left < right) {
        while (left < right && num[right] >= pivort) {
            right--;
        }
        num[left] = num[right];
        while (left < right && num[left] <= pivort) {
            left++;
        }
        num[right] = num[left];
    }
    num[left] = pivort;
    return left;
}

void sort(vector<int>& num, int left, int right) {
    if (left >= right) return;
    int mid = partition(num, left, right);
    sort(num, left, mid - 1);
    sort(num, mid + 1, right);
    return;
}

int main() {
    vector<int> data{4, 2, 1, 5, 9};
    sort(data, 0, data.size() - 1);
    return 0;
}
