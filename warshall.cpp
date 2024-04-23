#include <iostream>
#include <vector>

using namespace std;

// �����ڽӾ���Ĵ�С
const int MAXN = 100;

// Warshall �㷨��հ�����
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
    cout << "�������ڽӾ���Ĵ�С����/��������";
    cin >> n;

    // �����ڽӾ���
    vector<vector<int>> graph(n, vector<int>(n));

    cout << "�������ڽӾ���" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> graph[i][j];
        }
    }

    // ��հ�����
    warshall(graph, n);

    // ����հ�����
    cout << "�հ�����" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
