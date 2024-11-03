#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to;
    int weight;
};

void readGraph(const string& filename, vector<vector<Edge>>& graph, int& n) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    int m;
    file >> n >> m;  // Зчитуємо кількість вершин n та кількість ребер m
    graph.resize(n + 1);  // Створюємо граф розміром n+1 (для зручності нумерації з 1)

    for (int i = 0; i < m; ++i) {
        int v, u, w;
        file >> v >> u >> w;  // Зчитуємо ребро (v, u) з вагою w
        graph[v].push_back({ u, w });
    }

    file.close();
}

vector<int> dijkstra(const vector<vector<Edge>>& graph, int start) {
    int n = graph.size() - 1;
    vector<int> distances(n + 1, INF);
    distances[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int current_distance = pq.top().first;
        int current_vertex = pq.top().second;
        pq.pop();

        if (current_distance > distances[current_vertex])
            continue;

        for (const auto& edge : graph[current_vertex]) {
            int neighbor = edge.to;
            int weight = edge.weight;
            int distance = current_distance + weight;

            if (distance < distances[neighbor]) {
                distances[neighbor] = distance;
                pq.push({ distance, neighbor });
            }
        }
    }

    return distances;
}

void findShortestPath(const vector<vector<Edge>>& graph, int start, int end) {
    vector<int> distances = dijkstra(graph, start);

    if (distances[end] == INF) {
        cout << "No path exists from " << start << " to " << end << endl;
    }
    else {
        cout << "Shortest distance from " << start << " to " << end << ": " << distances[end] << endl;
    }
}

int main() {
    string filename = "input.txt";  // Вкажіть шлях до файлу з графом
    vector<vector<Edge>> graph;
    int n;

    readGraph(filename, graph, n);

    int start, end;
    cout << "Enter start vertex: ";
    cin >> start;
    cout << "Enter end vertex: ";
    cin >> end;

    // Найкоротший шлях між двома вершинами
    findShortestPath(graph, start, end);

    // Найкоротші відстані від заданої вершини до всіх інших вершин
    vector<int> distances = dijkstra(graph, start);
    cout << "Shortest distances from vertex " << start << " to all vertices:" << endl;
    for (int i = 1; i <= n; ++i) {
        if (distances[i] == INF) {
            cout << "Vertex " << i << ": No path" << endl;
        }
        else {
            cout << "Vertex " << i << ": " << distances[i] << endl;
        }
    }

    return 0;
}
