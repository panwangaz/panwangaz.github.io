#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    double x;
    double y;
};

struct RotatedBox {
    Point center;
    double width;
    double height;
    double angle; // 以弧度表示的旋转角度
};

std::vector<Point> getBoxVertices(const RotatedBox& box) {
    double w = box.width / 2;
    double h = box.height / 2;
    double sinA = sin(box.angle);
    double cosA = cos(box.angle);
    double cx = box.center.x;
    double cy = box.center.y;
    std::vector<Point> vertices = {
        {cx + w * cosA - h * sinA, cy + w * sinA + h * cosA},
        {cx + w * cosA + h * sinA, cy + w * sinA - h * cosA},
        {cx - w * cosA + h * sinA, cy - w * sinA - h * cosA},
        {cx - w * cosA - h * sinA, cy - w * sinA + h * cosA}
    };
    return vertices;
}

double getPolygonArea(const std::vector<Point>& vertices) {
    int n = vertices.size();
    double area = 0.0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += vertices[i].x * vertices[j].y - vertices[j].x * vertices[i].y;
    }
    return 0.5 * std::abs(area);
}

double getIntersectionArea(const RotatedBox& box1, const RotatedBox& box2) {
    std::vector<Point> vertices1 = getBoxVertices(box1);
    std::vector<Point> vertices2 = getBoxVertices(box2);
    std::vector<Point> vertices;
    for (const auto& vertex : vertices1) {
        if (vertex.x >= box2.center.x - box2.width / 2 &&
            vertex.x <= box2.center.x + box2.width / 2 &&
            vertex.y >= box2.center.y - box2.height / 2 &&
            vertex.y <= box2.center.y + box2.height / 2) {
            vertices.push_back(vertex);
        }
    }
    for (const auto& vertex : vertices2) {
        if (vertex.x >= box1.center.x - box1.width / 2 &&
            vertex.x <= box1.center.x + box1.width / 2 &&
            vertex.y >= box1.center.y - box1.height / 2 &&
            vertex.y <= box1.center.y + box1.height / 2) {
            vertices.push_back(vertex);
        }
    }
    double area = getPolygonArea(vertices);
    return area;
}

double getIoU(const RotatedBox& box1, const RotatedBox& box2) {
    double area1 = box1.width * box1.height;
    double area2 = box2.width * box2.height;
    double intersectionArea = getIntersectionArea(box1, box2);
    double unionArea = area1 + area2 - intersectionArea;
    double iou = intersectionArea / unionArea;
    return iou;
}

int main() {
    RotatedBox box1 = {{0, 0}, 2, 1, M_PI_4};
    RotatedBox box2 = {{1, 1}, 2, 1, M_PI_4};
    double iou = getIoU(box1, box2);
    std::cout << "IoU: " << iou << std::endl;
    return 0;
}
