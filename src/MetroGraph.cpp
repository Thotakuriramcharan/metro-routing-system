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