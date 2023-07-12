#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// 定义数据点结构体
struct Point {
    double x;
    double y;
};

// 计算两点之间的距离
double distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// 更新聚类中心
void updateCentroids(vector<Point>& centroids, const vector<vector<Point>>& clusters) {
    for (int i = 0; i < centroids.size(); ++i) {
        double sum_x = 0, sum_y = 0;
        int count = clusters[i].size();
        for (int j = 0; j < count; ++j) {
            sum_x += clusters[i][j].x;
            sum_y += clusters[i][j].y;
        }
        centroids[i].x = sum_x / count;
        centroids[i].y = sum_y / count;
    }
}

// K-Means 算法函数
void kmeans(int k, vector<Point>& points) {
    // 随机选择 k 个点作为聚类中心
    vector<Point> centroids(k);
    srand((unsigned)time(NULL));
    for (int i = 0; i < k; ++i) {
        centroids[i].x = points[rand() % points.size()].x;
        centroids[i].y = points[rand() % points.size()].y;
    }

    // 迭代聚类
    vector<vector<Point>> clusters(k);
    int max_iter = 10;
    while (max_iter--) {
        // 将每个数据点分配到最近的聚类中心
        for (int i = 0; i < points.size(); ++i) {
            double min_dist = distance(points[i], centroids[0]);
            int min_index = 0;
            for (int j = 1; j < k; ++j) {
                double dist = distance(points[i], centroids[j]);
                if (dist < min_dist) {
                    min_dist = dist;
                    min_index = j;
                }
            }
            clusters[min_index].push_back(points[i]);
        }

        // 更新聚类中心
        updateCentroids(centroids, clusters);

        // 清除聚类集合
        for (int i = 0; i < k; ++i) {
            clusters[i].clear();
        }
    }

    // 输出聚类结果
    for (int i = 0; i < k; ++i) {
        cout << "Cluster " << i << ": ";
        for (int j = 0; j < clusters[i].size(); ++j) {
            cout << "(" << clusters[i][j].x << ", " << clusters[i][j].y << ") ";
        }
        cout << endl;
    }
}

int main() {
    // 生成数据点
    vector<Point> points(20);
    srand((unsigned)time(NULL));
    for (int i = 0; i < 20; ++i) {
        points[i].x = rand() % 100;
        points[i].y = rand() % 100;
    }

    // 调用 K-Means 算法
    kmeans(3, points);

    return 0;
}
