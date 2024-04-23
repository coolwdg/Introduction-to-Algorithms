#include <iostream>
#include <vector>

using namespace std;

// 定义邻接矩阵的大小
const int MAXN = 100;
const int INF = 1e9;

// Floyd-Warshall 算法求解最短路径
void floyd_warshall(vector<vector<int>>& graph, int n) {
    // 初始化距离矩阵
    vector<vector<int>> dist(n, vector<int>(n));

    // 初始化距离矩阵为邻接矩阵
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = graph[i][j];
        }
    }

    // 更新距离矩阵
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // 输出最短路径
    cout << "最短路径：" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF) {
                cout << -1 << " ";
            }
            else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "请输入节点数量：";
    cin >> n;

    // 定义邻接矩阵
    vector<vector<int>> graph(n, vector<int>(n));

    cout << "请输入有向图的邻接矩阵：" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
            if (graph[i][j] == -1) {
                // 无法通过的路径用 INF 表示
                graph[i][j] = INF;
            }
        }
    }

    // 调用 Floyd-Warshall 算法求解最短路径
    floyd_warshall(graph, n);

    return 0;
}
