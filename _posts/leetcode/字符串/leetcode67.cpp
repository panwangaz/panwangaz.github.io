#include<string>
#include<climits>
#include<iostream>
using namespace std;


class Solution {
public:
    int strToInt(string str) {
        int i = 0;
        while (str[i] == ' ') {
            i++;
        }
        // str = str.substr(i, str.size() - i);
        bool flag = false;
        if ((str[i] != '+' && str[i] != '-') && (str[i] > '9' || str[i] < '0')) return 0;
        if (str[i] == '+') {
            i++;
        }
        else if (str[i] == '-') {
            i++;
            flag = true;
        }
        long long res = 0;
        for (int j = i; j < str.size(); j++) {
            if (str[j] > '9' || str[j] < '0') break;
            if (res * 10 + str[j] - '0' > INT_MAX) return flag ? INT_MIN : INT_MAX;
            res = res * 10 + str[j] - '0';
        }
        return flag ? -1 * res : res;
    }
};

int main() {
    Solution solver = Solution();
    string str = "-91283472332";
    int res = solver.strToInt(str);
    cout << res << endl;
    return 0;
}
