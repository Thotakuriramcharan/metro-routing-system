#ifndef ROUTE_RESULT_H
#define ROUTE_RESULT_H
#include <bits/stdc++.h>
using namespace std;
struct RouteResult {
    bool routeExists;
    vector<int> path;
    double totalDistanceKm;
    int stops;
    int interchanges;
    vector<string> linesUsed;
    string routeType;
};
struct RouteComparison {
    RouteResult bfsResult;
    RouteResult dijkstraResult;
};
#endif