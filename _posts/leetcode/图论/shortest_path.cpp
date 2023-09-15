#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> bfs_shortest_path(const vector<vector<int>>& graph, int start, int end) {
    vector<bool> visited(graph.size(), false);
    queue<pair<int, vector<int>>> q;
    q.push({start, {}});

    while (!q.empty()) {
        int node = q.front().first;
        vector<int> path = q.front().second;
        q.pop();
        visited[node] = true;

        if (node == end) {
            path.push_back(node);
            return path;
        }

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                // vector<int> new_path = path;
                // new_path.push_back(node);
                path.push_back(node);
                q.push({neighbor, path});
            }
        }
    }

    return {};
}

int main() {
    vector<vector<int>> graph = {
        {1, 2},
        {0, 3, 4},
        {0, 5},
        {1},
        {1, 5},
        {2, 4}
    };

    int start_node = 0;  // 节点索引从0开始
    int end_node = 5;
    vector<int> shortest_path = bfs_shortest_path(graph, start_node, end_node);

    if (!shortest_path.empty()) {
        cout << "最短路径: ";
        for (int node : shortest_path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "无法找到路径" << endl;
    }

    return 0;
}