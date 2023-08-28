#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x, y;
};

// 计算两个点构成的向量的叉积
int crossProduct(const Point& p1, const Point& p2, const Point& p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

// 判断多边形是否为凸边形
bool isConvexPolygon(const vector<Point>& polygon) {
    int n = polygon.size();

    // 遍历每个顶点
    for (int i = 0; i < n; i++) {
        int cp = crossProduct(polygon[i], polygon[(i + 1) % n], polygon[(i + 2) % n]);

        // 如果相邻边的转向不一致，多边形不是凸边形
        if (cp * crossProduct(polygon[i], polygon[(i + 1) % n], polygon[(i + 3) % n]) < 0) {
            return false;
        }
    }

    // 所有相邻边的转向一致，多边形是凸边形
    return true;
}

int main() {
    int n;
    while (cin >> n && n > 0) {
        vector<Point> polygon(n);
        for (int i = 0; i < n; i++) {
            cin >> polygon[i].x >> polygon[i].y;
        }

        if (isConvexPolygon(polygon)) {
            cout << "convex" << endl;
        } else {
            cout << "concave" << endl;
        }
    }

    return 0;
}