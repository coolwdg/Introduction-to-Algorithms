#include <iostream>
#include <vector>

using namespace std;

// 定义邻接矩阵的大小
const int MAXN = 100;

// Warshall 算法求闭包矩阵
void warshall(vector<vector<int>>& graph, int n) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                graph[i][j] = graph[i][j] || (graph[i][k] && graph[k][j]);
            }
        }
    }
}

int main() {
    int n;
    cout << "请输入邻接矩阵的大小（行/列数）：";
    cin >> n;

    // 定义邻接矩阵
    vector<vector<int>> graph(n, vector<int>(n));

    cout << "请输入邻接矩阵：" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    // 求闭包矩阵
    warshall(graph, n);

    // 输出闭包矩阵
    cout << "闭包矩阵：" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
