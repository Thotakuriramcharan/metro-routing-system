#ifndef ROUTE_ENGINE_H
#define ROUTE_ENGINE_H
#include <bits/stdc++.h>
#include "MetroGraph.h"
#include "RouteResult.h"
using namespace std;
class RouteEngine {
public:
    RouteResult minimumStopsRoute(
        const MetroGraph& graph,
        int source,
        int destination
    );
    RouteResult shortestDistanceRoute(
        const MetroGraph& graph,
        int source,
        int destination
    );
    RouteComparison compareRoutes(
        const MetroGraph& graph,
        int source,
        int destination
    );
};
#endif