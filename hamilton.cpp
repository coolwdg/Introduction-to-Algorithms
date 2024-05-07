#include <iostream>
#include <vector>

using namespace std;
char w[7] = { 'a','b','c','d','e','f','g' };

// ��鵱ǰ�����Ƿ���Լ���·��
bool isSafe(int v, vector<int>& path, int pos, vector<vector<int>>& graph) {
    // ��鵱ǰ��������һ�������Ƿ��б�
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // ��鵱ǰ�����Ƿ��Ѿ���·����
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

// ���ݺ���
void hamiltonianCycleUtil(vector<vector<int>>& graph, vector<int>& path, int pos, vector<vector<int>>& allPaths) {
    int V = graph.size();

    // ���ж��㶼�ѱ�����
    if (pos == V) {
        // ������һ������͵�һ�������Ƿ��б�
        if (graph[path[pos - 1]][path[0]] == 1) {
            allPaths.push_back(path);
        }
        return;
    }

    // ������Ӳ�ͬ�Ķ��㵽·����
    for (int v = 0; v < V; v++) {
        if (isSafe(v, path, pos, graph)) {
            path[pos] = v;
            hamiltonianCycleUtil(graph, path, pos + 1, allPaths);
            // �����Ӷ���v���ܵõ���Ч·���������
            path[pos] = -1;
        }
    }
}

// ������
void hamiltonianCycle(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> path(V, -1);
    vector<vector<int>> allPaths;
    path[0] = 0;

    hamiltonianCycleUtil(graph, path, 1, allPaths);

    // ��ӡ���й��ܶٻ�·
    if (allPaths.empty()) {
        cout << "No Hamiltonian cycles exist in the graph." << endl;
    }
    else {
        for (const auto& p : allPaths) {
            for (int i = 0; i < V; i++) {
                cout << w[p[i]] << "->";
            }
            cout << w[p[0]] << endl; // �ص���ʼ����
        }
    }
}
int main() {
    // �ڽӾ����ʾ��ͼ
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