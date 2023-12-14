#include<vector>
#include<iostream>
using namespace std;

void print_vector(vector<int>& input) {
    int size = input.size();
    for(int i = 0; i < size; i++) {
        cout << input[i] << endl;
    }
    return;
}
