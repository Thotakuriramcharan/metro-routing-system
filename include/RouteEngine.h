#ifndef ROUTE_ENGINE_H
#define ROUTE_ENGINE_H
#include <bits/stdc++.h>
#include "MetroGraph.h"
using namespace std;
struct RouteResult {
    bool found;
    vector<int> path;
    int stops;
};
class RouteEngine {
public:
    RouteResult minimumStopsRoute(
        const MetroGraph& graph,
        int source,
        int destination
    );
};
#endif