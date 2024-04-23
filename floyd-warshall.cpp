#include <iostream>
#include <vector>

using namespace std;

// �����ڽӾ���Ĵ�С
const int MAXN = 100;
const int INF = 1e9;

// Floyd-Warshall �㷨������·��
void floyd_warshall(vector<vector<int>>& graph, int n) {
    // ��ʼ���������
    vector<vector<int>> dist(n, vector<int>(n));

    // ��ʼ���������Ϊ�ڽӾ���
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = graph[i][j];
        }
    }

    // ���¾������
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // ������·��
    cout << "���·����" << endl;
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
    cout << "������ڵ�������";
    cin >> n;

    // �����ڽӾ���
    vector<vector<int>> graph(n, vector<int>(n));

    cout << "����������ͼ���ڽӾ���" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
            if (graph[i][j] == -1) {
                // �޷�ͨ����·���� INF ��ʾ
                graph[i][j] = INF;
            }
        }
    }

    // ���� Floyd-Warshall �㷨������·��
    floyd_warshall(graph, n);

    return 0;
}
