#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <chrono> // For timing
#include <queue>
using namespace std;
using namespace std::chrono;

// 定义最大顶点数
#define MAX_VERTICES 100

// 边的结构体
struct Edge {
    int src, dest, weight;
};

// 生成随机图
vector<Edge> generateRandomGraph(int V, double density) {
    vector<Edge> edges;

    // 生成随机边
    srand(time(NULL));
    for (int i = 1; i <= V; ++i) {
        for (int j = i + 1; j <= V; ++j) {
            if ((double)rand() / RAND_MAX < density) {
                int weight = rand() % 100 + 1; // 随机生成边的权重
                edges.push_back({ i, j, weight });
            }
        }
    }

    // 确保图连通性
    vector<vector<int>> adjacency(V + 1, vector<int>(V + 1, 0)); // 邻接矩阵
    for (const Edge& edge : edges) {
        adjacency[edge.src][edge.dest] = 1;
        adjacency[edge.dest][edge.src] = 1;
    }

    // 使用广度优先搜索（BFS）检查图的连通性
    vector<bool> visited(V + 1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 1; v <= V; ++v) {
            if (adjacency[u][v] && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    // 如果有未访问的节点，则添加额外的边以确保连通性
    for (int i = 2; i <= V; ++i) {
        if (!visited[i]) {
            int j = rand() % (i - 1) + 1; // 随机选择一个已访问的节点
            int weight = rand() % 100 + 1; // 随机生成边的权重
            edges.push_back({ i, j, weight }); // 添加额外的边
            adjacency[i][j] = 1;
            adjacency[j][i] = 1;
        }
    }

    return edges;
}

// Kruskal算法
vector<Edge> kruskal(vector<Edge>& edges, int V) {
    // 根据权重对边进行排序
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
        });

    vector<Edge> MST; // 用于存储最小生成树的边
    vector<int> parent(V + 1); // 用于存储顶点的父节点

    // 初始化父节点数组，每个顶点的父节点都是自己
    for (int i = 1; i <= V; ++i) {
        parent[i] = i;
    }

    // 遍历所有边，如果两个顶点不在同一棵树中，则将它们加入最小生成树
    for (Edge& edge : edges) {
        int rootSrc = edge.src;
        int rootDest = edge.dest;
        while (rootSrc != parent[rootSrc]) {
            rootSrc = parent[rootSrc];
        }
        while (rootDest != parent[rootDest]) {
            rootDest = parent[rootDest];
        }

        if (rootSrc != rootDest) { // 如果两个顶点不在同一棵树中
            MST.push_back(edge);
            parent[rootSrc] = rootDest; // 将其中一个顶点的根节点设为另一个顶点的根节点
        }
    }

    return MST;
}

// Prim算法
vector<Edge> prim(vector<vector<int>>& graph, int V) {
    vector<Edge> MST; // 用于存储最小生成树的边
    vector<int> key(V + 1, INT_MAX); // 用于存储顶点的键值
    vector<bool> inMST(V + 1, false); // 用于标记顶点是否在最小生成树中

    key[1] = 0; // 将第一个顶点作为起始点

    // 依次加入 V-1 个顶点到最小生成树中
    for (int count = 0; count < V - 1; ++count) {
        int minKey = INT_MAX;
        int minIndex = -1;

        // 从不在最小生成树中的顶点中选择键值最小的顶点
        for (int v = 1; v <= V; ++v) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }

        inMST[minIndex] = true;

        // 更新相邻顶点的键值
        for (int v = 1; v <= V; ++v) {
            if (graph[minIndex][v] && !inMST[v] && graph[minIndex][v] < key[v]) {
                key[v] = graph[minIndex][v];
            }
        }
    }

    // 构建最小生成树的边集合
    for (int v = 2; v <= V; ++v) {
        MST.push_back({ v, v - 1, key[v] });
    }

    return MST;
}

int main() {
    int V; // 顶点数
    double density; // 图的密度

    cout << "Enter the number of vertices: ";
    cin >> V;

    cout << "Enter the density of the graph (0 to 1): ";
    cin >> density;

    // 生成随机图
    vector<Edge> edges = generateRandomGraph(V, density);

    // 构建邻接矩阵表示的图
    vector<vector<int>> graph(V + 1, vector<int>(V + 1, 0));
    for (Edge& edge : edges) {
        graph[edge.src][edge.dest] = edge.weight;
        graph[edge.dest][edge.src] = edge.weight;
    }

    // 测量Kruskal算法的运行时间
    auto start = high_resolution_clock::now();
    vector<Edge> MST_kruskal = kruskal(edges, V);
    auto stop = high_resolution_clock::now();
    auto duration_kruskal = duration_cast<microseconds>(stop - start);
    cout << "Kruskal Algorithm Time: " << duration_kruskal.count() << " microseconds\n";

    // 测量Prim算法的运行时间
    start = high_resolution_clock::now();
    vector<Edge> MST_prim = prim(graph, V);
    stop = high_resolution_clock::now();
    auto duration_prim = duration_cast<microseconds>(stop - start);
    cout << "Prim Algorithm Time: " << duration_prim.count() << " microseconds\n";

    return 0;
}
