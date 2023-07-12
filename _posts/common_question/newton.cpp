#include<vector>
#include<cmath>
#include<iostream>
using namespace std;

// class Solver {
// public:
//     float x0 = 2.0;
//     float forward(float x);
//     float calGrad(float x, float delta);
//     void newtonSolve(float x, float eps, float lr);
// };

// float Solver::forward(float input) {
//     return log(input) + input * input;
// }

// float Solver::calGrad(float input, float delta=1e-3) {
//     float dy = forward(input + delta) - forward(input);
//     return dy / delta;
// }

// void Solver::newtonSolve(float x, float eps=1e-3, float lr=1e-3) {
//     float val = forward(x);
//     while (abs(val) > eps) {
//         float grad = calGrad(val);
//         cout << "grad: " << grad << endl;
//         x = x - grad * lr;
//         val = forward(x);
//         cout << "update value: " << val << endl;
//     }
//     return;
// }

int main() {
    // Solver sol = Solver();
    // sol.newtonSolve(sol.x0);
    float x0 = 30.0;
    while (abs(log(x0) + x0*x0) > 1e-3) {
        x0 -= (pow(x0, 3) + x0 * log(x0)) / (2 * x0 * x0 + 1);
        cout << "val: " << x0 << endl;
    }
    return 0;
}
