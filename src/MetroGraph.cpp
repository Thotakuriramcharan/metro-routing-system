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
    if (closedStations.count(stationId)) {
        return {};
    }
    vector<Edge> result;
    for (const auto& edge : it->second) {
        if (edge.getStatus() == Status::CLOSED) {
            continue;
        }
        if (closedStations.count(edge.getTo())) {
            continue;
        }
        result.push_back(edge);
    }
    return result;
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
bool MetroGraph::hasConnection(int from, int to) const {
    auto it = adjacency.find(from);
    if (it == adjacency.end()) {
        return false;
    }
    for (const auto& edge : it->second) {
        if (edge.getTo() == to) {
            return true;
        }
    }
    return false;
}
bool MetroGraph::removeConnection(int from, int to) {
    auto fromIt = adjacency.find(from);
    auto toIt = adjacency.find(to);
    if (fromIt == adjacency.end() || toIt == adjacency.end()) {
        return false;
    }
    auto& fromEdges = fromIt->second;
    fromEdges.erase(
        remove_if(
            fromEdges.begin(),
            fromEdges.end(),
            [to](const Edge& edge) {
                return edge.getTo() == to;
            }
        ),
        fromEdges.end()
    );
    auto& toEdges = toIt->second;
    toEdges.erase(
        remove_if(
            toEdges.begin(),
            toEdges.end(),
            [from](const Edge& edge) {
                return edge.getTo() == from;
            }
        ),
        toEdges.end()
    );
    return true;
}
vector<Edge> MetroGraph::listConnections() const {
    vector<Edge> connections;
    for (const auto& [id, edges] : adjacency) {
        for (const auto& edge : edges) {
            if (edge.getFrom() < edge.getTo()) {
                connections.push_back(edge);
            }
        }
    }
    return connections;
}
bool MetroGraph::closeStation(int stationId) {
    if (adjacency.find(stationId) == adjacency.end()) {
        return false;
    }
    closedStations.insert(stationId);
    return true;
}
bool MetroGraph::reopenStation(int stationId) {
    if (adjacency.find(stationId) == adjacency.end()) {
        return false;
    }
    closedStations.erase(stationId);
    return true;
}
bool MetroGraph::closeConnection(int from, int to) {
    auto fromIt = adjacency.find(from);
    auto toIt = adjacency.find(to);
    if (fromIt == adjacency.end() || toIt == adjacency.end()) {
        return false;
    }
    bool found = false;
    for (auto& edge : fromIt->second) {
        if (edge.getTo() == to) {
            edge.setClosed();
            found = true;
        }
    }
    for (auto& edge : toIt->second) {
        if (edge.getTo() == from) {
            edge.setClosed();
            found = true;
        }
    }
    return found;
}
bool MetroGraph::reopenConnection(int from, int to) {
    auto fromIt = adjacency.find(from);
    auto toIt = adjacency.find(to);
    if (fromIt == adjacency.end() || toIt == adjacency.end()) {
        return false;
    }
    bool found = false;
    for (auto& edge : fromIt->second) {
        if (edge.getTo() == to) {
            edge.setOpen();
            found = true;
        }
    }
    for (auto& edge : toIt->second) {
        if (edge.getTo() == from) {
            edge.setOpen();
            found = true;
        }
    }
    return found;
}
