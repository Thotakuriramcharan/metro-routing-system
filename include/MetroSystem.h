#ifndef METRO_SYSTEM_H
#define METRO_SYSTEM_H
#include <bits/stdc++.h>
#include "MetroGraph.h"
#include "Station.h"
#include "Edge.h"
using namespace std;
class MetroSystem {
private:
    MetroGraph graph;
    vector<Station> stations;
public:
    bool addStation(const Station& station);
    bool removeStation(int id);
    Station* findStation(int id);
    vector<Station> searchStationsByName(const string& query) const;
    vector<Station> listStations() const;
    vector<Station> listStationsByLine(const string& line) const;
    bool addConnection(int from, int to, double distanceKm);
    bool removeConnection(int from, int to);
    bool closeStation(int id);
    bool reopenStation(int id);
    bool closeConnection(int from, int to);
    bool reopenConnection(int from, int to);
    vector<Edge> listConnections() const;
    const MetroGraph& getGraph() const;
    bool saveNetwork(const string& filename) const;
    bool loadNetwork(const string& filename);
};
#endif