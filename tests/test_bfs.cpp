#include <gtest/gtest.h>
#include <gtest/gtest.h>
#include "../include/RouteEngine.h"
TEST(BFS, DirectRoute) {
    MetroGraph graph;

    graph.addStation(Station(1, "A", {"Blue"}, false));
    graph.addStation(Station(2, "B", {"Blue"}, false));

    graph.addConnection(1, 2, 2.0);

    RouteEngine engine;

    RouteResult result = engine.minimumStopsRoute(graph, 1, 2);

    EXPECT_TRUE(result.routeExists);
    EXPECT_EQ(result.stops, 1);
    EXPECT_EQ(result.path, vector<int>({1, 2}));
}
TEST(BFS, MultiHopRoute) {
    MetroGraph graph;

    graph.addStation(Station(1, "A", {"Blue"}, false));
    graph.addStation(Station(2, "B", {"Blue"}, false));
    graph.addStation(Station(3, "C", {"Blue"}, false));
    graph.addStation(Station(4, "D", {"Blue"}, false));

    graph.addConnection(1, 2, 1.0);
    graph.addConnection(2, 3, 1.0);
    graph.addConnection(3, 4, 1.0);

    RouteEngine engine;

    RouteResult result = engine.minimumStopsRoute(graph, 1, 4);

    EXPECT_TRUE(result.routeExists);
    EXPECT_EQ(result.stops, 3);
    EXPECT_EQ(result.path, vector<int>({1, 2, 3, 4}));
}
TEST(BFS, UnreachableDestination) {
    MetroGraph graph;

    graph.addStation(Station(1, "A", {"Blue"}, false));
    graph.addStation(Station(2, "B", {"Blue"}, false));
    graph.addStation(Station(3, "C", {"Blue"}, false));

    graph.addConnection(1, 2, 1.0);

    RouteEngine engine;

    RouteResult result = engine.minimumStopsRoute(graph, 1, 3);

    EXPECT_FALSE(result.routeExists);
    EXPECT_EQ(result.stops, -1);
    EXPECT_TRUE(result.path.empty());
}
TEST(BFS, SameSourceDestination) {
    MetroGraph graph;

    graph.addStation(Station(1, "A", {"Blue"}, false));

    RouteEngine engine;

    RouteResult result = engine.minimumStopsRoute(graph, 1, 1);

    EXPECT_TRUE(result.routeExists);
    EXPECT_EQ(result.stops, 0);
    EXPECT_EQ(result.path, vector<int>({1}));
}