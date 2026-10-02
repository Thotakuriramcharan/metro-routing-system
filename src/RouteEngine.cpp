#include "../include/RouteEngine.h"
RouteResult RouteEngine::minimumStopsRoute(
    const MetroGraph& graph,
    int source,
    int destination
) {
    int n = 1000; // temporary, we'll improve this later
    vector<int> visited(n, 0);
    vector<int> parent(n, -1);
    vector<int> distance(n, -1);
    queue<int> q;
    visited[source] = 1;
    distance[source] = 0;
    q.push(source);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        if (node == destination) {
            break;
        }
        for (const auto& edge : graph.neighbours(node)) {
            int next = edge.getTo();
            if (!visited[next]) {
                visited[next] = 1;
                parent[next] = node;
                distance[next] = distance[node] + 1;
                q.push(next);
            }
        }
    }
    if (!visited[destination]) {
        return {false, {}, -1};
    }
    vector<int> path;
    int current = destination;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());
    return {true, path, distance[destination]};
   }
