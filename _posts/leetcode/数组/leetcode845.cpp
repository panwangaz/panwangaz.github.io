#include<vector>
#include<iostream>
#include<algorithm>
#include<limits.h>
using namespace std;

vector<int> solver(vector<int>& data) {
    int size = data.size();
    if (size <= 1) return {};
    vector<int> left(size, 1);
    int pre = data[0], ans = 1;
    for (int i = 1; i < size; i++) {
        if (data[i] > pre) {
            ans += 1;
            left[i] = ans;
            pre = data[i];
        }
        else {
            pre = data[i];
            ans = 1;
        }
    }
    return left;
}

int main() {
    vector<int> data{2, 1, 4, 7, 3, 2, 5};
    int size = data.size();
    vector<int> left = solver(data);
    reverse(data.begin(), data.end());
    vector<int> right = solver(data);
    vector<int> res(size, 0);
    for (int i = 0; i < left.size(); i++) {
        res[i] = left[i] + right[i] - 1;
    }
    while (res.size() >= 1) {
        cout << "ans: " << res[res.size() - 1] << endl;
        res.pop_back();
    }

    return 0;
}
