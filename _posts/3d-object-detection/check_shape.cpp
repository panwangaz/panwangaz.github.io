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

bool isConvexPolygon(const vector<Point>& polygon) {
    for (int i = 0; i < polygon.size(); i++) {
        int cur = crossProduct(polygon[(i + 1) % n], polygon[i], polygon[(i + 2) % n]);
        // 如果相邻边的转向不一致，多边形不是凸边形
        if (cur < 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int n = 3;
    vector<vector<int>> data{{1, 2}, {2, 3}, {3, 4}};
    vector<Point> polygon(n);
    for (int i = 0; i < n; i++) {
        polygon[i].x = data[i][0];
        polygon[i].y = data[i][1];
    }

    if (isConvexPolygon(polygon)) {
        cout << "convex" << endl;
    } else {
        cout << "concave" << endl;
    }

    return 0;
}