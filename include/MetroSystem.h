#ifndef METRO_SYSTEM_H
#define METRO_SYSTEM_H
#include <bits/stdc++.h>
#include "MetroGraph.h"
#include "Station.h"
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
};
#endif