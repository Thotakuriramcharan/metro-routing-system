#ifndef METRO_GRAPH_H
#define METRO_GRAPH_H
#include <bits/stdc++.h>
#include "Station.h"
#include "Edge.h"
using namespace std;
class MetroGraph {
private:
    unordered_map<int, vector<Edge>> adjacency;
    unordered_set<int> closedStations;
public:
    void addStation(const Station& station);
    void addConnection(int from, int to, double distanceKm);
    vector<Edge> neighbours(int stationId) const;
    bool removeStation(int stationId);
    bool removeConnection(int from, int to);
    bool hasConnection(int from, int to) const;
    bool closeStation(int stationId);
    bool reopenStation(int stationId);
    bool closeConnection(int from, int to);
    bool reopenConnection(int from, int to);
    vector<Edge> listConnections() const;
};
#endif