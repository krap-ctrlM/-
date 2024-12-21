#include <iostream>
#include <vector>
#include <chrono> 


using namespace std;
using namespace chrono;

const int MAXN = 100;

// Объявление функции dfs
void dfs(vector<vector<int>>& graph, int u, vector<bool>& visited);

// Функция для проверки условий задачи
bool isValidGraph(vector<vector<int>>& graph) {
    int n = graph.size();
    
    // Проверка наличия связности 2
    int connectedComponents = 0;
    vector<bool> visited(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(graph, i, visited);
            connectedComponents++;
        }
    }

    if (connectedComponents != 1) {
        cout << "Граф не имеет вершинной связности 2. Эйлеров путь не существует." << endl;
        return false;
    }

    // Проверка связности графа и наличия петель
    for (int i = 0; i < n; ++i) {
        if (graph[i][i] != 0) {
            cout << "Граф содержит петлю в вершине " << i << ". Эйлеров путь не существует." << endl;
            return false;
        }
        for (int j = 0; j < n; ++j) {
            if (graph[i][j] != 0 && graph[j][i] == 0) {
                cout << "Граф несвязанный. Эйлеров путь не существует." << endl;
                return false;
            }
        }
    }

    // Проверка равенства весов рёбер
    int weight = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (graph[i][j] != 0) {
                if (weight == -1) {
                    weight = graph[i][j];
                } else if (weight != graph[i][j]) {
                    cout << "Веса рёбер не равны. Эйлеров путь не существует." << endl;
                    return false;
                }
            }
        }
    }

    return true;
}

// Функция для выполнения обхода в глубину
void dfs(vector<vector<int>>& graph, int u, vector<bool>& visited) {
    visited[u] = true;
    for (int v = 0; v < graph.size(); ++v) {
        if (graph[u][v] != 0 && !visited[v]) {
            dfs(graph, v, visited);
        }
    }
}

// Функция для нахождения эйлерова пути
void findEulerPath(vector<vector<int>>& graph, vector<int>& path, int u, int& totalWeight) {
    for (int v = 0; v < graph.size(); ++v) {
        if (graph[u][v] != 0) {
            totalWeight += graph[u][v];  
            graph[u][v] = graph[v][u] = 0; 
            findEulerPath(graph, path, v, totalWeight);
        }
    }
    path.push_back(u);
}

