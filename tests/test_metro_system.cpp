#include <gtest/gtest.h>
#include "../include/MetroSystem.h"
TEST(MetroSystem, RejectsDuplicateId) {
    MetroSystem system;
    Station s1(1, "Central", {"Blue"}, false);
    Station s2(1, "Airport", {"Blue"}, false);
    EXPECT_TRUE(system.addStation(s1));
    EXPECT_FALSE(system.addStation(s2));
    EXPECT_EQ(system.listStations().size(), 1);
}
TEST(MetroSystem, RejectsDuplicateName) {
    MetroSystem system;
    Station s1(1, "Central", {"Blue"}, false);
    Station s2(2, "Central", {"Red"}, false);
    EXPECT_TRUE(system.addStation(s1));
    EXPECT_FALSE(system.addStation(s2));
    EXPECT_EQ(system.listStations().size(), 1);
}
TEST(MetroSystem, RejectsRemovingNonexistentStation) {
    MetroSystem system;
    Station s1(1, "Central", {"Blue"}, false);
    system.addStation(s1);
    EXPECT_FALSE(system.removeStation(99));
    EXPECT_EQ(system.listStations().size(), 1);
}
TEST(MetroSystem, SearchesStationsByPartialName) {
    MetroSystem system;
    Station s1(1, "Central", {"Blue"}, false);
    Station s2(2, "Tech Park", {"Yellow"}, false);
    Station s3(3, "Airport", {"Orange"}, false);
    system.addStation(s1);
    system.addStation(s2);
    system.addStation(s3);
    vector<Station> results = system.searchStationsByName("tech");
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].getName(), "Tech Park");
}