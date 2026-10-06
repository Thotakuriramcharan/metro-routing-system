#include <gtest/gtest.h>
#include "../include/MetroSystem.h"
#include "../include/RouteEngine.h"
#include "../include/RouteResult.h"
TEST(MetroSystem, RejectsConnectionWithNonexistentStation) {
    MetroSystem system;
    Station s1(1, "Central", {"Blue"}, false);
    system.addStation(s1);
    EXPECT_FALSE(system.addConnection(1, 99, 2.0));
    EXPECT_EQ(system.listConnections().size(), 0);
}
TEST(MetroSystem, RejectsDuplicateConnection) {
    MetroSystem system;
    Station s1(1, "Central", {"Blue"}, false);
    Station s2(2, "Airport", {"Blue"}, false);
    system.addStation(s1);
    system.addStation(s2);
    EXPECT_TRUE(system.addConnection(1, 2, 2.0));
    EXPECT_FALSE(system.addConnection(2, 1, 2.0));
    EXPECT_EQ(system.listConnections().size(), 1);
}
TEST(MetroSystem, RejectsInvalidConnectionDistance) {
    MetroSystem system;
    Station s1(1, "Central", {"Blue"}, false);
    Station s2(2, "Airport", {"Blue"}, false);
    system.addStation(s1);
    system.addStation(s2);
    EXPECT_FALSE(system.addConnection(1, 2, 0.0));
    EXPECT_FALSE(system.addConnection(1, 2, -5.0));
    EXPECT_EQ(system.listConnections().size(), 0);
}
TEST(MetroSystem, RemovingConnectionChangesRoute) {
    MetroSystem system;
    Station s1(1, "A", {"Blue"}, false);
    Station s2(2, "B", {"Blue"}, false);
    Station s3(3, "C", {"Blue"}, false);
    system.addStation(s1);
    system.addStation(s2);
    system.addStation(s3);
    system.addConnection(1, 2, 1.0);
    system.addConnection(2, 3, 1.0);
    RouteEngine engine;
    RouteResult before = engine.minimumStopsRoute(
        system.getGraph(), 1, 3
    );
    EXPECT_TRUE(before.routeExists);
    EXPECT_TRUE(system.removeConnection(2, 3));
    RouteResult after = engine.minimumStopsRoute(
        system.getGraph(), 1, 3
    );
    EXPECT_FALSE(after.routeExists);
}