#include<bits/stdc++.h>
using namespace std;
#include "../include/MetroGraph.h"
#include "../include/RouteEngine.h"
#include "../include/Edge.h"
#include "../include/Station.h"
int main(){
    ifstream file("data/metro_network.txt");
    if (!file) {
        cout << "Could not open network file" << endl;
        return 1;
    }
    string line;
    bool readingStations = false;
    bool readingConnections = false;
    vector<Station> loadedStations;
    vector<Edge> loadedEdges;
    while (getline(file, line)) {
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
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, lineNames, ',');
            if (id.empty() || name.empty() || lineNames.empty()) {
                cout << "Invalid station line: " << line << endl;
                continue;
            }
            int stationId = stoi(id);
            vector<string> lines;
            stringstream lineStream(lineNames);
            string currentLine;
            while (getline(lineStream, currentLine, '|')) {
                if (!currentLine.empty()) {
                    lines.push_back(currentLine);
                }
            }
            bool isInterchange = lines.size() > 1;
            Station station(stationId, name, lines, isInterchange);
            loadedStations.push_back(station);
        }
        if (readingConnections) {
            stringstream ss(line);
            string from;
            string to;
            string distance;
            getline(ss, from, ',');
            getline(ss, to, ',');
            getline(ss, distance, ',');
            int fromId = stoi(from);
            int toId = stoi(to);
            double distanceKm = stod(distance);
            Edge edge(fromId, toId, distanceKm);
            loadedEdges.push_back(edge);
        }
    }
    cout << "Loaded " << loadedStations.size()
         << " stations and "
         << loadedEdges.size()
         << " connections" << endl;
    MetroGraph graph;
    for (const auto& station : loadedStations) {
        graph.addStation(station);
    }
    for (const auto& edge : loadedEdges) {
        graph.addConnection(
            edge.getFrom(),
            edge.getTo(),
            edge.getDistance()
        );
    }
    return 0;
}