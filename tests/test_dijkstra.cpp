#include <gtest/gtest.h>
#include "../include/RouteEngine.h"
TEST(Dijkstra, DirectWeightedRoute) {
    MetroGraph graph;

    graph.addStation(Station(1, "A", {"Blue"}, false));
    graph.addStation(Station(2, "B", {"Blue"}, false));

    graph.addConnection(1, 2, 5.0);

    RouteEngine engine;

    RouteResult result = engine.shortestDistanceRoute(graph, 1, 2);

    EXPECT_TRUE(result.routeExists);
    EXPECT_EQ(result.path, vector<int>({1, 2}));
    EXPECT_DOUBLE_EQ(result.totalDistanceKm, 5.0);
}
TEST(Dijkstra, ChoosesLowerDistanceRoute) {
    MetroGraph graph;

    graph.addStation(Station(10, "A", {"Blue"}, false));
    graph.addStation(Station(11, "B", {"Blue"}, false));
    graph.addStation(Station(12, "C", {"Red"}, false));
    graph.addStation(Station(13, "D", {"Red"}, false));
    graph.addStation(Station(14, "E", {"Green"}, false));

    graph.addConnection(10, 11, 2.0);
    graph.addConnection(11, 14, 8.0);

    graph.addConnection(10, 12, 1.0);
    graph.addConnection(12, 13, 1.0);
    graph.addConnection(13, 14, 1.0);

    RouteEngine engine;

    RouteResult result =
        engine.shortestDistanceRoute(graph, 10, 14);

    EXPECT_TRUE(result.routeExists);
    EXPECT_EQ(result.path, vector<int>({10, 12, 13, 14}));
    EXPECT_DOUBLE_EQ(result.totalDistanceKm, 3.0);
}
TEST(Dijkstra, UnreachableDestination) {
    MetroGraph graph;

    graph.addStation(Station(1, "A", {"Blue"}, false));
    graph.addStation(Station(2, "B", {"Blue"}, false));
    graph.addStation(Station(3, "C", {"Red"}, false));

    graph.addConnection(1, 2, 2.0);

    RouteEngine engine;

    RouteResult result =
        engine.shortestDistanceRoute(graph, 1, 3);

    EXPECT_FALSE(result.routeExists);
    EXPECT_EQ(result.totalDistanceKm, -1.0);
    EXPECT_TRUE(result.path.empty());
}
TEST(Dijkstra, CorrectTotalDistance) {
    MetroGraph graph;

    graph.addStation(Station(1, "A", {"Blue"}, false));
    graph.addStation(Station(2, "B", {"Blue"}, false));
    graph.addStation(Station(3, "C", {"Blue"}, false));

    graph.addConnection(1, 2, 2.5);
    graph.addConnection(2, 3, 3.5);

    RouteEngine engine;

    RouteResult result =
        engine.shortestDistanceRoute(graph, 1, 3);

    EXPECT_TRUE(result.routeExists);
    EXPECT_EQ(result.path, vector<int>({1, 2, 3}));
    EXPECT_DOUBLE_EQ(result.totalDistanceKm, 6.0);
}
TEST(Dijkstra, InvalidStationId) {
    MetroGraph graph;

    Station a(1, "A", {"Blue"}, false);
    Station b(2, "B", {"Blue"}, false);

    graph.addStation(a);
    graph.addStation(b);
    graph.addConnection(1, 2, 2.0);

    RouteEngine engine;

    RouteResult result = engine.shortestDistanceRoute(graph, 1, 9999);

    EXPECT_FALSE(result.routeExists);
}