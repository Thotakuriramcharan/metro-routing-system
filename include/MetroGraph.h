#ifndef METRO_GRAPH_H
#define METRO_GRAPH_H
#include <bits/stdc++.h>
#include "Station.h"
#include "Edge.h"
using namespace std;
class MetroGraph {
private:
    unordered_map<int, vector<Edge>> adjacency;
public:
    void addStation(const Station& station);
    void addConnection(int from, int to, double distanceKm);
    vector<Edge> neighbours(int stationId) const;
};
#endif