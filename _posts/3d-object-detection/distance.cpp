#include <iostream>
#include <cmath>
using namespace std;

// 定义向量类
class Vector {
public:
    double x, y;
    Vector(double x = 0, double y = 0) : x(x), y(y) {}
};

Vector operator+(Vector A, Vector B) {
    return Vector(A.x + B.x, A.y + B.y);
}

Vector operator-(Vector A, Vector B) {
    return Vector(A.x - B.x, A.y - B.y);
}

Vector operator*(Vector A, double p) {
    return Vector(A.x * p, A.y * p);
}

Vector operator/(Vector A, double p) {
    return Vector(A.x / p, A.y / p);
}

double Dot(Vector A, Vector B) {
    return A.x * B.x + A.y * B.y;
}

double Length(Vector A) {
    return sqrt(Dot(A, A));
}

double DistanceToLine(Vector P, Vector A, Vector B) {
    Vector AP = P - A;
    Vector AB = B - A;
    double lenAB = Length(AB);
    Vector projAP = AB * (Dot(AP, AB) / (lenAB * lenAB));
    return Length(AP - projAP);
}

int main() {
    Vector P(1, 2);
    Vector A(-1, 0);
    Vector B(3, 0);
    double dist = DistanceToLine(P, A, B);
    cout << "Distance from P to line AB: " << dist << endl;
    return 0;
}
