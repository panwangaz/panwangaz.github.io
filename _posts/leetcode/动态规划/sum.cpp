#include<vector>
#include<iostream>
using namespace std;

bool solve(vector<int>& data, int target) {
    int size = data.size();
    vector<vector<bool>> dp(size, vector<bool>(target + 1, false));
    for (int i = 0; i < size; i++) {
        dp[i][0] = true;
    }
    dp[0][data[0]] = true;
    for (int i = 1; i < size; i++) {
        for (int s = 1; s <= target; s++) {
            if (data[i] > s) continue;
            dp[i][s] = dp[i - 1][s];
            dp[i][s] = dp[i - 1][s - data[i]];
            if (dp[i][s]) return true;
        }
    }
    return false;
}

int main() {
    vector<int> data{3,34,4,12,5,2};
    int target = 9;
    bool flag = solve(data, target);
    cout << "res: " << flag << endl;
    return 0;

}
