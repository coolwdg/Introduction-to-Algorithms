#include <iostream>
#include <vector>

using namespace std;
char w[7] = { 'a','b','c','d','e','f','g' };

// 检查当前顶点是否可以加入路径
bool isSafe(int v, vector<int>& path, int pos, vector<vector<int>>& graph) {
    // 检查当前顶点和最后一个顶点是否有边
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // 检查当前顶点是否已经在路径中
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

// 回溯函数
void hamiltonianCycleUtil(vector<vector<int>>& graph, vector<int>& path, int pos, vector<vector<int>>& allPaths) {
    int V = graph.size();

    // 所有顶点都已被访问
    if (pos == V) {
        // 检查最后一个顶点和第一个顶点是否有边
        if (graph[path[pos - 1]][path[0]] == 1) {
            allPaths.push_back(path);
        }
        return;
    }

    // 尝试添加不同的顶点到路径中
    for (int v = 0; v < V; v++) {
        if (isSafe(v, path, pos, graph)) {
            path[pos] = v;
            hamiltonianCycleUtil(graph, path, pos + 1, allPaths);
            // 如果添加顶点v不能得到有效路径，则回溯
            path[pos] = -1;
        }
    }
}

// 主函数
void hamiltonianCycle(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> path(V, -1);
    vector<vector<int>> allPaths;
    path[0] = 0;

    hamiltonianCycleUtil(graph, path, 1, allPaths);

    // 打印所有哈密顿回路
    if (allPaths.empty()) {
        cout << "No Hamiltonian cycles exist in the graph." << endl;
    }
    else {
        for (const auto& p : allPaths) {
            for (int i = 0; i < V; i++) {
                cout << w[p[i]] << "->";
            }
            cout << w[p[0]] << endl; // 回到起始顶点
        }
    }
}
int main() {
    // 邻接矩阵表示的图
    vector<vector<int>> graph = {
        {0, 1, 1, 1, 0, 1, 0},
        {1, 0, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0},
        {1, 1, 0, 0, 0, 1, 1},
        {0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 1},
        {0, 1, 0, 1, 1, 1, 0}
    };

    hamiltonianCycle(graph);

    return 0;
}