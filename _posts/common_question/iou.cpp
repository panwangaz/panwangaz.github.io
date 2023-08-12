#include <iostream>

struct Rectangle {
    int x;      // 矩形左上角 x 坐标
    int y;      // 矩形左上角 y 坐标
    int width;  // 矩形宽度
    int height; // 矩形高度
};

// 计算两个矩形框的交集面积
int CalculateIntersectionArea(const Rectangle& rect1, const Rectangle& rect2) {
    int x1 = std::max(rect1.x, rect2.x);
    int y1 = std::max(rect1.y, rect2.y);
    int x2 = std::min(rect1.x + rect1.width, rect2.x + rect2.width);
    int y2 = std::min(rect1.y + rect1.height, rect2.y + rect2.height);

    int intersectionWidth = std::max(0, x2 - x1);
    int intersectionHeight = std::max(0, y2 - y1);

    return intersectionWidth * intersectionHeight;
}

// 计算两个矩形框的并集面积
int CalculateUnionArea(const Rectangle& rect1, const Rectangle& rect2) {
    int rect1Area = rect1.width * rect1.height;
    int rect2Area = rect2.width * rect2.height;
    int intersectionArea = CalculateIntersectionArea(rect1, rect2);

    return rect1Area + rect2Area - intersectionArea;
}

// 计算IoU
double CalculateIoU(const Rectangle& rect1, const Rectangle& rect2) {
    int intersectionArea = CalculateIntersectionArea(rect1, rect2);
    int unionArea = CalculateUnionArea(rect1, rect2);

    return static_cast<double>(intersectionArea) / unionArea;
}

int main() {
    Rectangle rect1 = { 0, 0, 5, 5 };
    Rectangle rect2 = { 3, 3, 6, 6 };

    double iou = CalculateIoU(rect1, rect2);
    std::cout << "IoU: " << iou << std::endl;

    return 0;
}