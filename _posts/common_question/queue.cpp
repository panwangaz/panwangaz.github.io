#include<iostream>
#include<vector>
using namespace std;

class Myqueue {
public:
    Myqueue():m_input({}), m_output({}) {}
    Myqueue(vector<int> input, vector<int> output):m_input(input), m_output(output) {}

public:
    void push(int val);
    int pop();
    bool empty();

private:
    vector<int> m_input, m_output;
    int pop_output();
};

void Myqueue::push(int val) {
    m_input.push_back(val);
    return;
}

int Myqueue::pop_output() {
    if (!m_output.empty()) {
        int val = m_output.back();
        m_output.pop_back();
        return val;
    }
    return -1;
}

int Myqueue::pop() {
    if (!m_output.empty()) {
        return pop_output();
    }
    else {
        if (!m_input.empty()) {
            while (!m_input.empty()) {
                int cur = m_input.back();
                m_input.pop_back();
                m_output.push_back(cur);
            }
            return pop_output();
        }
    }
    return -1;
}

bool Myqueue::empty() {
    return m_input.size() == 0 && m_output.size() == 0;
}


int main() {
    Myqueue que = Myqueue({3, 4, 5}, {});
    que.push(1);
    que.push(2);
    que.push(3);
    while (!que.empty()) {
        cout << que.pop() << endl;
    }

    return 0;
}