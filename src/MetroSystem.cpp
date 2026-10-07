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
bool MetroSystem::closeConnection(int from, int to) {
    return graph.closeConnection(from, to);
}
bool MetroSystem::reopenConnection(int from, int to) {
    return graph.reopenConnection(from, to);
}
vector<Edge> MetroSystem::listConnections() const {
    return graph.listConnections();
}
const MetroGraph& MetroSystem::getGraph() const {
    return graph;
}
bool MetroSystem::closeStation(int id) {
    Station* station = findStation(id);
    if (station == nullptr) {
        return false;
    }
    station->setClose();
    graph.closeStation(id);
    return true;
}

bool MetroSystem::reopenStation(int id) {
    Station* station = findStation(id);
    if (station == nullptr) {
        return false;
    }
    station->setOpen();
    graph.reopenStation(id);
    return true;
}
bool MetroSystem::saveNetwork(const string& filename) const {
    ofstream file(filename);
    if (!file) {
        return false;
    }
    file << "#STATIONS\n";
    for (const auto& station : stations) {
        file << station.getId() << ",";
        file << station.getName() << ",";
        const auto lines = station.getLines();
        for (size_t i = 0; i < lines.size(); ++i) {
            if (i > 0) {
                file << "|";
            }
            file << lines[i];
        }
        file << ",";
        if (station.getStatus() == Status::OPEN) {
            file << "OPEN";
        } else {
        file << "CLOSED";
    }
    file << "\n";
    }
    file << "\n#CONNECTIONS\n";
    for (const auto& edge : listConnections()) {
        file << edge.getFrom() << ",";
        file << edge.getTo() << ",";
        file << edge.getDistance() << ",";
        if (edge.getStatus() == Status::OPEN) {
            file << "OPEN";
        } else {
            file << "CLOSED";
        }
        file << "\n";
    }
    return true;
}
bool MetroSystem::loadNetwork(const string& filename) {
    ifstream file(filename);
    if (!file) {
        return false;
    }
    MetroSystem temp;
    string line;
    bool readingStations = false;
    bool readingConnections = false;
    int lineNumber = 0;
    while (getline(file, line)) {
        lineNumber++;
        if (line.empty()) {
            continue;
        }
        if (line == "#STATIONS") {
            readingStations = true;
            readingConnections = false;
            continue;
        }
        if (line == "#CONNECTIONS") {
            readingStations = false;
            readingConnections = true;
            continue;
        }
        if (readingStations) {
            stringstream ss(line);
            string id;
            string name;
            string lineNames;
            string status;
            if (!getline(ss, id, ',') ||
                !getline(ss, name, ',') ||
                !getline(ss, lineNames, ',') ||
                !getline(ss, status)) {
                    cout << "Invalid station data at line "
                         << lineNumber << endl;
                    return false;
                }
                if (status != "OPEN" && status != "CLOSED") {
                    cout << "Invalid station data at line "
                         << lineNumber << endl;
                    return false;
                }
            int stationId;
            try {
                size_t idPos;
                stationId = stoi(id, &idPos);
                if (idPos != id.size()) {
                    cout << "Invalid station data at line "
                         << lineNumber << endl;
                         return false;
                }
            } catch (...) {
                cout << "Invalid station data at line "
                     << lineNumber << endl;
                     return false;
            }
            vector<string> lines;
            stringstream lineStream(lineNames);
            string currentLine;
            while (getline(lineStream, currentLine, '|')) {
                if (!currentLine.empty()) {
                    lines.push_back(currentLine);
                }
            }
            if (lines.empty()) {
                cout << "Invalid station data at line " << lineNumber << endl;
                return false;
            }
            bool isInterchange = lines.size() > 1;
            Station station(
                stationId,
                name,
                lines,
                isInterchange
            );
            if (status == "CLOSED") {
                station.setClose();
            } else if (status == "OPEN") {
                station.setOpen();
            } else {
                cout << "Invalid station data at line " << lineNumber << endl;
                return false;
            }
            if (!temp.addStation(station)) {
                cout << "Invalid station data at line " << lineNumber << endl;
                return false;
            }
            if (status == "CLOSED") {
                if (!temp.closeStation(stationId)) {
                    return false;
                }
            }
        }
        if (readingConnections) {
            stringstream ss(line);
            string from;
            string to;
            string distance;
            string status;
            if (!getline(ss, from, ',') ||
            !getline(ss, to, ',') ||
            !getline(ss, distance, ',') ||
            !getline(ss, status, ',')) {
                cout << "Invalid connection data at line "
                << lineNumber << endl;
                return false;
            }
            int fromId;
            int toId;
            double distanceKm;
            try {
                size_t fromPos;
                size_t toPos;
                size_t distancePos;
                fromId = stoi(from, &fromPos);
                toId = stoi(to, &toPos);
                distanceKm = stod(distance, &distancePos);
                if (fromPos != from.size() ||
                toPos != to.size() ||
                distancePos != distance.size()) {
                    cout << "Invalid connection values at line "
                    << lineNumber << endl;
                    return false;
                }
            } catch (...) {
                cout << "Invalid connection values at line "
                << lineNumber << endl;
                return false;
            }
            if (!temp.addConnection(fromId, toId, distanceKm)) {
                cout << "Invalid connection at line "
                << lineNumber << endl;
                return false;
            }
            if (status == "CLOSED") {
                if (!temp.closeConnection(fromId, toId)) {
                    cout << "Invalid connection state at line "
                    << lineNumber << endl;
                    return false;
                }
            } else if (status != "OPEN") {
                cout << "Invalid connection status at line "
                << lineNumber << endl;
                return false;
            }
        }
    }
    *this = temp;
    return true;
}