#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <chrono> // For timing
#include <queue>
using namespace std;
using namespace std::chrono;

// ������󶥵���
#define MAX_VERTICES 100

// �ߵĽṹ��
struct Edge {
    int src, dest, weight;
};

// �������ͼ
vector<Edge> generateRandomGraph(int V, double density) {
    vector<Edge> edges;

    // ���������
    srand(time(NULL));
    for (int i = 1; i <= V; ++i) {
        for (int j = i + 1; j <= V; ++j) {
            if ((double)rand() / RAND_MAX < density) {
                int weight = rand() % 100 + 1; // ������ɱߵ�Ȩ��
                edges.push_back({ i, j, weight });
            }
        }
    }

    // ȷ��ͼ��ͨ��
    vector<vector<int>> adjacency(V + 1, vector<int>(V + 1, 0)); // �ڽӾ���
    for (const Edge& edge : edges) {
        adjacency[edge.src][edge.dest] = 1;
        adjacency[edge.dest][edge.src] = 1;
    }

    // ʹ�ù������������BFS�����ͼ����ͨ��
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

    // �����δ���ʵĽڵ㣬����Ӷ���ı���ȷ����ͨ��
    for (int i = 2; i <= V; ++i) {
        if (!visited[i]) {
            int j = rand() % (i - 1) + 1; // ���ѡ��һ���ѷ��ʵĽڵ�
            int weight = rand() % 100 + 1; // ������ɱߵ�Ȩ��
            edges.push_back({ i, j, weight }); // ��Ӷ���ı�
            adjacency[i][j] = 1;
            adjacency[j][i] = 1;
        }
    }

    return edges;
}

// Kruskal�㷨
vector<Edge> kruskal(vector<Edge>& edges, int V) {
    // ����Ȩ�ضԱ߽�������
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
        });

    vector<Edge> MST; // ���ڴ洢��С�������ı�
    vector<int> parent(V + 1); // ���ڴ洢����ĸ��ڵ�

    // ��ʼ�����ڵ����飬ÿ������ĸ��ڵ㶼���Լ�
    for (int i = 1; i <= V; ++i) {
        parent[i] = i;
    }

    // �������бߣ�����������㲻��ͬһ�����У������Ǽ�����С������
    for (Edge& edge : edges) {
        int rootSrc = edge.src;
        int rootDest = edge.dest;
        while (rootSrc != parent[rootSrc]) {
            rootSrc = parent[rootSrc];
        }
        while (rootDest != parent[rootDest]) {
            rootDest = parent[rootDest];
        }

        if (rootSrc != rootDest) { // ����������㲻��ͬһ������
            MST.push_back(edge);
            parent[rootSrc] = rootDest; // ������һ������ĸ��ڵ���Ϊ��һ������ĸ��ڵ�
        }
    }

    return MST;
}

// Prim�㷨
vector<Edge> prim(vector<vector<int>>& graph, int V) {
    vector<Edge> MST; // ���ڴ洢��С�������ı�
    vector<int> key(V + 1, INT_MAX); // ���ڴ洢����ļ�ֵ
    vector<bool> inMST(V + 1, false); // ���ڱ�Ƕ����Ƿ�����С��������

    key[1] = 0; // ����һ��������Ϊ��ʼ��

    // ���μ��� V-1 �����㵽��С��������
    for (int count = 0; count < V - 1; ++count) {
        int minKey = INT_MAX;
        int minIndex = -1;

        // �Ӳ�����С�������еĶ�����ѡ���ֵ��С�Ķ���
        for (int v = 1; v <= V; ++v) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }

        inMST[minIndex] = true;

        // �������ڶ���ļ�ֵ
        for (int v = 1; v <= V; ++v) {
            if (graph[minIndex][v] && !inMST[v] && graph[minIndex][v] < key[v]) {
                key[v] = graph[minIndex][v];
            }
        }
    }

    // ������С�������ı߼���
    for (int v = 2; v <= V; ++v) {
        MST.push_back({ v, v - 1, key[v] });
    }

    return MST;
}

int main() {
    int V; // ������
    double density; // ͼ���ܶ�

    cout << "Enter the number of vertices: ";
    cin >> V;

    cout << "Enter the density of the graph (0 to 1): ";
    cin >> density;

    // �������ͼ
    vector<Edge> edges = generateRandomGraph(V, density);

    // �����ڽӾ����ʾ��ͼ
    vector<vector<int>> graph(V + 1, vector<int>(V + 1, 0));
    for (Edge& edge : edges) {
        graph[edge.src][edge.dest] = edge.weight;
        graph[edge.dest][edge.src] = edge.weight;
    }

    // ����Kruskal�㷨������ʱ��
    auto start = high_resolution_clock::now();
    vector<Edge> MST_kruskal = kruskal(edges, V);
    auto stop = high_resolution_clock::now();
    auto duration_kruskal = duration_cast<microseconds>(stop - start);
    cout << "Kruskal Algorithm Time: " << duration_kruskal.count() << " microseconds\n";

    // ����Prim�㷨������ʱ��
    start = high_resolution_clock::now();
    vector<Edge> MST_prim = prim(graph, V);
    stop = high_resolution_clock::now();
    auto duration_prim = duration_cast<microseconds>(stop - start);
    cout << "Prim Algorithm Time: " << duration_prim.count() << " microseconds\n";

    return 0;
}
