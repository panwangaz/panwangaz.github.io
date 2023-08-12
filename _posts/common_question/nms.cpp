#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct BoundingBox {
    float x, y, width, height, score;
};

float computeIoU(const BoundingBox& box1, const BoundingBox& box2) {
    float x1 = max(box1.x, box2.x);
    float y1 = max(box1.y, box2.y);
    float x2 = min(box1.x + box1.width, box2.x + box2.width);
    float y2 = min(box1.y + box1.height, box2.y + box2.height);

    float intersectionArea = max(0.0f, x2 - x1) * max(0.0f, y2 - y1);
    float box1Area = box1.width * box1.height;
    float box2Area = box2.width * box2.height;

    float iou = intersectionArea / (box1Area + box2Area - intersectionArea);
    return iou;
}

vector<BoundingBox> performNMS(const vector<BoundingBox>& boxes, float threshold) {
    vector<BoundingBox> sortedBoxes = boxes;
    sort(sortedBoxes.begin(), sortedBoxes.end(), [](const BoundingBox& a, const BoundingBox& b) {
        return a.score > b.score;
    });

    vector<BoundingBox> selectedBoxes;
    vector<bool> isBoxSelected(boxes.size(), false);

    for (size_t i = 0; i < sortedBoxes.size(); ++i) {
        if (isBoxSelected[i]) continue;
        selectedBoxes.push_back(sortedBoxes[i]);
        isBoxSelected[i] = true;

        for (size_t j = i + 1; j < sortedBoxes.size(); ++j) {
            if (computeIoU(sortedBoxes[i], sortedBoxes[j]) > threshold) {
                isBoxSelected[j] = true;
            }
        }
    }
    return selectedBoxes;
}

int main() {
    vector<BoundingBox> boxes = {
        { 10, 10, 100, 100, 0.9 },
        { 20, 20, 80, 80, 0.8 },
        { 30, 30, 120, 120, 0.75 },
        { 50, 50, 150, 150, 0.85 },
        { 200, 200, 100, 100, 0.95 }
    };

    float iouThreshold = 0.5;
    vector<BoundingBox> selectedBoxes = performNMS(boxes, iouThreshold);

    cout << "Selected Boxes: " << endl;
    for (const auto& box : selectedBoxes) {
        cout << "x: " << box.x << ", y: " << box.y
                  << ", width: " << box.width << ", height: " << box.height
                  << ", score: " << box.score << endl;
    }

    return 0;
}