#include "../include/MetroGraph.h"

void MetroGraph::addStation(const Station& station) {
    adjacency[station.getId()];
}
void MetroGraph::addConnection(int from, int to, double distanceKm) {
    Edge edge1(from, to, distanceKm);
    Edge edge2(to, from, distanceKm);
    adjacency[from].push_back(edge1);
    adjacency[to].push_back(edge2);
}
vector<Edge> MetroGraph::neighbours(int stationId) const {
    auto it = adjacency.find(stationId);
    if (it == adjacency.end()) {
        return {};
    }
    return it->second;
}
bool MetroGraph::removeStation(int stationId) {
    auto it = adjacency.find(stationId);
    if (it == adjacency.end()) {
        return false;
    }
    adjacency.erase(it);
    for (auto& [id, edges] : adjacency) {
        edges.erase(
            remove_if(
                edges.begin(),
                edges.end(),
                [stationId](const Edge& edge) {
                    return edge.getTo() == stationId;
                }
            ),
            edges.end()
        );
    }
    return true;
}