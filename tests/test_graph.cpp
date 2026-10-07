#include <gtest/gtest.h>
#include "../include/MetroGraph.h"
#include "../include/Station.h"

TEST(GraphTest, AddsAndFindsStation) {
    MetroGraph graph;

    Station station(
        1,
        "Central",
        {"Blue"},
        false
    );

    graph.addStation(station);

    EXPECT_TRUE(graph.hasStation(1));
    EXPECT_FALSE(graph.hasStation(999));
}

TEST(GraphTest, AddsConnectionAndReturnsNeighbour) {
    MetroGraph graph;

    graph.addStation(Station(1, "Central", {"Blue"}, false));
    graph.addStation(Station(2, "Market", {"Blue"}, false));

    graph.addConnection(1, 2, 2.5);

    auto neighbours = graph.neighbours(1);

    ASSERT_EQ(neighbours.size(), 1);
    EXPECT_EQ(neighbours[0].getTo(), 2);
    EXPECT_DOUBLE_EQ(neighbours[0].getDistance(), 2.5);
}

TEST(GraphTest, ClosedStationIsExcludedFromNeighbours) {
    MetroGraph graph;

    graph.addStation(Station(1, "Central", {"Blue"}, false));
    graph.addStation(Station(2, "Market", {"Blue"}, false));

    graph.addConnection(1, 2, 2.5);

    ASSERT_TRUE(graph.closeStation(2));

    auto neighbours = graph.neighbours(1);

    EXPECT_TRUE(neighbours.empty());
}

TEST(GraphTest, ClosedConnectionIsExcludedFromNeighbours) {
    MetroGraph graph;

    graph.addStation(Station(1, "Central", {"Blue"}, false));
    graph.addStation(Station(2, "Market", {"Blue"}, false));

    graph.addConnection(1, 2, 2.5);

    ASSERT_TRUE(graph.closeConnection(1, 2));

    auto neighbours = graph.neighbours(1);

    EXPECT_TRUE(neighbours.empty());
}

TEST(GraphTest, ReopeningRestoresNeighbour) {
    MetroGraph graph;

    graph.addStation(Station(1, "Central", {"Blue"}, false));
    graph.addStation(Station(2, "Market", {"Blue"}, false));

    graph.addConnection(1, 2, 2.5);

    ASSERT_TRUE(graph.closeConnection(1, 2));
    ASSERT_TRUE(graph.reopenConnection(1, 2));

    auto neighbours = graph.neighbours(1);

    ASSERT_EQ(neighbours.size(), 1);
    EXPECT_EQ(neighbours[0].getTo(), 2);
}