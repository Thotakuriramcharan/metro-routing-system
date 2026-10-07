#include <gtest/gtest.h>
#include "../include/Station.h"

TEST(StationTest, CreatesStationCorrectly) {
    Station station(
        1,
        "Central",
        {"Blue", "Red"},
        true
    );

    EXPECT_EQ(station.getId(), 1);
    EXPECT_EQ(station.getName(), "Central");
    EXPECT_EQ(station.getLines().size(), 2);
    EXPECT_TRUE(station.getIsInterchange());
    EXPECT_EQ(station.getStatus(), Status::OPEN);
}

TEST(StationTest, StationCanBeClosedAndReopened) {
    Station station(
        1,
        "Central",
        {"Blue"},
        false
    );

    EXPECT_EQ(station.getStatus(), Status::OPEN);

    station.setClose();
    EXPECT_EQ(station.getStatus(), Status::CLOSED);

    station.setOpen();
    EXPECT_EQ(station.getStatus(), Status::OPEN);
}