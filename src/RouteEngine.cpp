#include "../include/RouteEngine.h"
RouteResult RouteEngine::minimumStopsRoute(const MetroGraph& graph,int source,int destination){
    if (!graph.hasStation(source) || !graph.hasStation(destination)) {
        return {false, {}, -1.0, -1, 0, {}, "Minimum Stops"};
    }
    unordered_set<int> visited;
    unordered_map<int, int> parent;
    unordered_map<int, int> distance;
    queue<int> q;
    visited.insert(source);
    distance[source] = 0;
    parent[source] = -1;
    q.push(source);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        if (node == destination) {
            break;
        }
        for (const auto& edge : graph.neighbours(node)) {
            int next = edge.getTo();
            if (!visited.count(next)) {
                visited.insert(next);
                parent[next] = node;
                distance[next] = distance[node] + 1;
                q.push(next);
            }
        }
    }
    if (!visited.count(destination)) {
        return {false, {}, -1.0, -1, 0, {}, "Minimum Stops"};
    }
    vector<int> path;
    int current = destination;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());
    return {true, path, 0.0, distance[destination], 0, {}, "Minimum Stops"};
}
RouteResult RouteEngine::shortestDistanceRoute( const MetroGraph& graph,int source,int destination){
    if (!graph.hasStation(source) || !graph.hasStation(destination)) {
        return {false, {}, -1.0, -1, 0, {}, "Shortest Distance"};
    }
    unordered_map<int, double> distance;
    unordered_map<int, int> parent;
    unordered_map<int, bool> processed;
    priority_queue<pair<double, int>,vector<pair<double, int>>,greater<pair<double, int>>> pq;
    distance[source] = 0.0;
    parent[source] = -1;
    processed[source] = false;
    pq.push({0.0, source});
    while (!pq.empty()) {
        auto [currentDistance, node] = pq.top();
        pq.pop();
        if (processed[node]) {
            continue;
        }
        processed[node] = true;
        for (const auto& edge : graph.neighbours(node)) {
            int next = edge.getTo();
            double weight = edge.getDistance();
            double newDistance = currentDistance + weight;
            if (!distance.count(next) || newDistance < distance[next]) {
                distance[next] = newDistance;
                parent[next] = node;
                processed[next] = false;
                pq.push({newDistance, next});
            }
        }
    }
    if (!distance.count(destination)) {
        return {false, {}, -1.0, -1, 0, {}, "Shortest Distance"};
    }
    vector<int> path;
    int current = destination;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());
    return {true,path,distance[destination],0,0,{},"Shortest Distance"};
}
RouteComparison RouteEngine::compareRoutes(const MetroGraph& graph,int source,int destination){
    RouteComparison comparison;
    comparison.bfsResult =
        minimumStopsRoute(graph, source, destination);
    comparison.dijkstraResult =
        shortestDistanceRoute(graph, source, destination);
    return comparison;
}
