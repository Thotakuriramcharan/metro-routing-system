#include <gtest/gtest.h>
#include "../include/MetroSystem.h"
#include "../include/RouteEngine.h"
#include "../include/RouteResult.h"
TEST(MetroSystem, ClosingStationForcesAlternativeRoute) {
    MetroSystem system;
    Station s1(1, "A", {"Blue"}, false);
    Station s2(2, "B", {"Blue"}, false);
    Station s3(3, "C", {"Red"}, false);
    Station s4(4, "D", {"Red"}, false);
    system.addStation(s1);
    system.addStation(s2);
    system.addStation(s3);
    system.addStation(s4);
    system.addConnection(1, 2, 1.0);
    system.addConnection(2, 4, 1.0);
    system.addConnection(1, 3, 2.0);
    system.addConnection(3, 4, 2.0);
    RouteEngine engine;
    RouteResult before =
        engine.minimumStopsRoute(system.getGraph(), 1, 4);
    ASSERT_TRUE(before.routeExists);
    EXPECT_TRUE(system.closeStation(2));
    RouteResult after =
        engine.minimumStopsRoute(system.getGraph(), 1, 4);
    ASSERT_TRUE(after.routeExists);
    EXPECT_EQ(after.path, (vector<int>{1, 3, 4}));
}
TEST(MetroSystem, ReopeningStationRestoresOriginalRoute) {
    MetroSystem system;
    Station s1(1, "A", {"Blue"}, false);
    Station s2(2, "B", {"Blue"}, false);
    Station s3(3, "C", {"Red"}, false);
    Station s4(4, "D", {"Red"}, false);
    system.addStation(s1);
    system.addStation(s2);
    system.addStation(s3);
    system.addStation(s4);
    system.addConnection(1, 2, 1.0);
    system.addConnection(2, 4, 1.0);
    system.addConnection(1, 3, 2.0);
    system.addConnection(3, 4, 2.0);
    RouteEngine engine;
    EXPECT_TRUE(system.closeStation(2));
    RouteResult closedRoute =
        engine.minimumStopsRoute(system.getGraph(), 1, 4);
    ASSERT_TRUE(closedRoute.routeExists);
    EXPECT_EQ(closedRoute.path, (vector<int>{1, 3, 4}));
    EXPECT_TRUE(system.reopenStation(2));
    RouteResult reopenedRoute =
        engine.minimumStopsRoute(system.getGraph(), 1, 4);
    ASSERT_TRUE(reopenedRoute.routeExists);
    EXPECT_EQ(reopenedRoute.path, (vector<int>{1, 2, 4}));
}
TEST(MetroSystem, ClosingConnectionForcesAlternativeRoute) {
    MetroSystem system;
    Station s1(1, "A", {"Blue"}, false);
    Station s2(2, "B", {"Blue"}, false);
    Station s3(3, "C", {"Red"}, false);
    Station s4(4, "D", {"Red"}, false);
    system.addStation(s1);
    system.addStation(s2);
    system.addStation(s3);
    system.addStation(s4);
    system.addConnection(1, 2, 1.0);
    system.addConnection(2, 4, 1.0);
    system.addConnection(1, 3, 2.0);
    system.addConnection(3, 4, 2.0);
    RouteEngine engine;
    RouteResult before =
        engine.minimumStopsRoute(system.getGraph(), 1, 4);
    ASSERT_TRUE(before.routeExists);
    EXPECT_EQ(before.path, (vector<int>{1, 2, 4}));
    EXPECT_TRUE(system.closeConnection(2, 4));
    RouteResult after =
        engine.minimumStopsRoute(system.getGraph(), 1, 4);
    ASSERT_TRUE(after.routeExists);
    EXPECT_EQ(after.path, (vector<int>{1, 3, 4}));
}
TEST(MetroSystem, FullyDisconnectedNetworkReturnsNoRoute) {
    MetroSystem system;
    Station s1(1, "A", {"Blue"}, false);
    Station s2(2, "B", {"Blue"}, false);
    system.addStation(s1);
    system.addStation(s2);
    system.addConnection(1, 2, 1.0);
    RouteEngine engine;
    RouteResult before =
        engine.minimumStopsRoute(system.getGraph(), 1, 2);
    ASSERT_TRUE(before.routeExists);
    EXPECT_TRUE(system.closeConnection(1, 2));
    RouteResult after =
        engine.minimumStopsRoute(system.getGraph(), 1, 2);
    EXPECT_FALSE(after.routeExists);
}