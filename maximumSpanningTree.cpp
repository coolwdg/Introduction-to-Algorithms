#include <iostream>
#include <vector>
#include <climits> // For INT_MAX
#include <algorithm>

using namespace std;

// 定义最大顶点数
#define MAX_VERTICES 100

// 最大生成树算法
void maximumSpanningTree(int graph[MAX_VERTICES][MAX_VERTICES], int V) {
    // 用于存储最大生成树的父节点数组
    int parent[MAX_VERTICES];

    // 用于存储顶点的键值，初始化为 INT_MIN
    int key[MAX_VERTICES];
    fill(key, key + V + 1, INT_MIN);

    // 用于标记顶点是否在最大生成树中
    bool inMST[MAX_VERTICES] = { false };

    // 将第一个顶点作为根节点
    parent[1] = -1; // 根节点没有父节点
    key[1] = INT_MAX; // 将根节点的键值设为 INT_MAX

    // 依次加入 V-1 个顶点到最大生成树中
    for (int count = 0; count < V; ++count) {
        // 初始化 maxIndex 和 maxKey
        int maxIndex = -1;
        int maxKey = INT_MIN;
        // 从不在最大生成树中的顶点中选择键值最大的顶点
        for (int v = 1; v <= V; ++v) {
            if (!inMST[v] && key[v] > maxKey) {
                maxKey = key[v];
                maxIndex = v;
            }
        }

        // 将选定的顶点加入最大生成树中
        inMST[maxIndex] = true;

        // 更新相邻顶点的键值
        for (int v = 1; v <= V; ++v) {
            if (graph[maxIndex][v] && !inMST[v] && graph[maxIndex][v] > key[v]) {
                parent[v] = maxIndex;
                key[v] = graph[maxIndex][v];
            }
        }
    }

    // 输出最大生成树的边
    cout << "Edges in the Maximum Spanning Tree:\n";
    for (int i = 2; i <= V; ++i) { // 从2开始，因为根节点没有父节点
        cout << parent[i] << " -- " << i << " : " << graph[i][parent[i]] << "\n";
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    // 初始化邻接矩阵，0 表示不相邻或不存在边
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };

    cout << "Enter the source, destination, and weight of each edge:\n";
    for (int i = 0; i < E; ++i) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph[src][dest] = weight;
        graph[dest][src] = weight; // 因为是无向图，所以需要对称填充
    }

    maximumSpanningTree(graph, V);

    return 0;
}
