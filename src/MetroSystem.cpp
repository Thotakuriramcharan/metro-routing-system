#include "../include/MetroSystem.h"
bool MetroSystem::addStation(const Station& station) {
    for(const auto& existing : stations) {
       if (existing.getId() == station.getId()) {
            return false;
       }
    }
    for(const auto& existing : stations) {
       if (existing.getName() == station.getName()) {
            return false;
       }
    }
    stations.push_back(station);
    graph.addStation(station);
    return true;
}
Station* MetroSystem::findStation(int id) {
    for (auto& station : stations) {
        if (station.getId() == id) {
            return &station;
        }
    }
    return nullptr;
}
vector<Station> MetroSystem::searchStationsByName(const string& query) const {
    vector<Station> results;
    string lowerQuery = query;
    transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);
    for (const auto& station : stations) {
        string lowerName = station.getName();
        transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
        if (lowerName.find(lowerQuery) != string::npos) {
            results.push_back(station);
        }
    }
    return results;
}
vector<Station> MetroSystem::listStations() const {
    return stations;
}
vector<Station> MetroSystem::listStationsByLine(const string& line) const {
    vector<Station> results;
    for (const auto& station : stations) {
        for (const auto& stationLine : station.getLines()) {
            if (stationLine == line) {
                results.push_back(station);
                break;
            }
        }
    }
    return results;
}
bool MetroSystem::removeStation(int id) {
    for (auto it = stations.begin(); it != stations.end(); ++it) {
        if (it->getId() == id) {
            graph.removeStation(id);
            stations.erase(it);
            return true;
        }
    }
    return false;
}
bool MetroSystem::addConnection(int from, int to, double distanceKm) {
    if (findStation(from) == nullptr) {
        return false;
    }
    if (findStation(to) == nullptr) {
        return false;
    }
    if (from == to) {
        return false;
    }
    if (graph.hasConnection(from, to)) {
        return false;
    }
    if (distanceKm <= 0) {
        return false;
    }
    graph.addConnection(from, to, distanceKm);
    return true;
}
bool MetroSystem::removeConnection(int from, int to) {
    if (!graph.hasConnection(from, to)) {
        return false;
    }
    return graph.removeConnection(from, to);
}
vector<Edge> MetroSystem::listConnections() const {
    return graph.listConnections();
}
const MetroGraph& MetroSystem::getGraph() const {
    return graph;
}