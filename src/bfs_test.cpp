#include <bits/stdc++.h>
using namespace std;

int bfs(vector<vector<int>>& graph, int source, int destination) {
    int n = graph.size();

    vector<int> visited(n, 0);
    vector<int> distance(n, -1);
    queue<int> q;

    visited[source] = 1;
    distance[source] = 0;
    q.push(source);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (node == destination) {
            return distance[node];
        }

        for (auto neighbour : graph[node]) {
            if (!visited[neighbour]) {
                visited[neighbour] = 1;
                distance[neighbour] = distance[node] + 1;
                q.push(neighbour);
            }
        }
    }

    return -1;
}

int main() {
    vector<vector<int>> testGraph = {
        {1},
        {0, 2},
        {1, 3},
        {2}
    };

    cout << "3-hop test: " << bfs(testGraph, 0, 3) << endl;

    return 0;
}