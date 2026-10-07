#include <bits/stdc++.h>
#include "MetroSystem.h"
#include "RouteEngine.h"
using namespace std;
int main() {
    MetroSystem system;
    if (!system.loadNetwork("data/metro_network.txt")) {
        cerr << "Failed to load network\n";
        return 1;
    }
    const MetroGraph& graph = system.getGraph();
    RouteEngine engine;
    int source = 10;
    int destination = 40;
    cout << "Benchmarking route "
         << source << " -> " << destination << "\n";
    cout << "Network: 51 stations, 54 connections\n";
    const int runs = 1000;
    long long totalTime = 0;
    for (int i = 0; i < runs; i++) {
        auto start = chrono::steady_clock::now();
        auto result = engine.minimumStopsRoute(
            graph,
            source,
            destination
        );
        auto end = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(
            end - start
        ).count();
        totalTime += duration;
    }
    double averageTime =
    static_cast<double>(totalTime) / runs;
    cout << "BFS average time: "
         << averageTime
         << " microseconds\n";
    totalTime = 0;
    for (int i = 0; i < runs; i++) {
        auto start = chrono::steady_clock::now();
        auto result = engine.shortestDistanceRoute(
            graph,
            source,
            destination
        );
    auto end = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(
        end - start
    ).count();
    totalTime += duration;
    }
    averageTime =
        static_cast<double>(totalTime) / runs;
    cout << "Dijkstra average time: "
         << averageTime
         << " microseconds\n";
    return 0;
}