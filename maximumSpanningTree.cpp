#include <iostream>
#include <vector>
#include <climits> // For INT_MAX
#include <algorithm>

using namespace std;

// ������󶥵���
#define MAX_VERTICES 100

// ����������㷨
void maximumSpanningTree(int graph[MAX_VERTICES][MAX_VERTICES], int V) {
    // ���ڴ洢����������ĸ��ڵ�����
    int parent[MAX_VERTICES];

    // ���ڴ洢����ļ�ֵ����ʼ��Ϊ INT_MIN
    int key[MAX_VERTICES];
    fill(key, key + V + 1, INT_MIN);

    // ���ڱ�Ƕ����Ƿ��������������
    bool inMST[MAX_VERTICES] = { false };

    // ����һ��������Ϊ���ڵ�
    parent[1] = -1; // ���ڵ�û�и��ڵ�
    key[1] = INT_MAX; // �����ڵ�ļ�ֵ��Ϊ INT_MAX

    // ���μ��� V-1 �����㵽�����������
    for (int count = 0; count < V; ++count) {
        // ��ʼ�� maxIndex �� maxKey
        int maxIndex = -1;
        int maxKey = INT_MIN;
        // �Ӳ�������������еĶ�����ѡ���ֵ���Ķ���
        for (int v = 1; v <= V; ++v) {
            if (!inMST[v] && key[v] > maxKey) {
                maxKey = key[v];
                maxIndex = v;
            }
        }

        // ��ѡ���Ķ�����������������
        inMST[maxIndex] = true;

        // �������ڶ���ļ�ֵ
        for (int v = 1; v <= V; ++v) {
            if (graph[maxIndex][v] && !inMST[v] && graph[maxIndex][v] > key[v]) {
                parent[v] = maxIndex;
                key[v] = graph[maxIndex][v];
            }
        }
    }

    // �������������ı�
    cout << "Edges in the Maximum Spanning Tree:\n";
    for (int i = 2; i <= V; ++i) { // ��2��ʼ����Ϊ���ڵ�û�и��ڵ�
        cout << parent[i] << " -- " << i << " : " << graph[i][parent[i]] << "\n";
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    // ��ʼ���ڽӾ���0 ��ʾ�����ڻ򲻴��ڱ�
    int graph[MAX_VERTICES][MAX_VERTICES] = { 0 };

    cout << "Enter the source, destination, and weight of each edge:\n";
    for (int i = 0; i < E; ++i) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph[src][dest] = weight;
        graph[dest][src] = weight; // ��Ϊ������ͼ��������Ҫ�Գ����
    }

    maximumSpanningTree(graph, V);

    return 0;
}
