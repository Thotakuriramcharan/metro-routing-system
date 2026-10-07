#include <gtest/gtest.h>
#include "../include/MetroSystem.h"
#include <fstream>
TEST(PersistenceTest, RejectsMalformedStationLine) {
    ofstream file("data/malformed_station.txt");
    file << "#STATIONS\n";
    file << "1,Central,Blue\n";
    file << "#CONNECTIONS\n";
    file.close();
    MetroSystem system;
    EXPECT_FALSE(system.loadNetwork("data/malformed_station.txt"));
}
TEST(PersistenceTest, RejectsNonNumericDistance) {
    ofstream file("data/malformed_distance.txt");
    file << "#STATIONS\n";
    file << "1,Central,Blue,OPEN\n";
    file << "2,Market,Blue,OPEN\n";
    file << "#CONNECTIONS\n";
    file << "1,2,abc,OPEN\n";
    file.close();
    MetroSystem system;
    EXPECT_FALSE(system.loadNetwork("data/malformed_distance.txt"));
}
TEST(PersistenceTest, RejectsPartiallyNumericDistance) {
    ofstream file("data/partially_numeric_distance.txt");
    file << "#STATIONS\n";
    file << "1,Central,Blue,OPEN\n";
    file << "2,Market,Blue,OPEN\n";
    file << "#CONNECTIONS\n";
    file << "1,2,12abc,OPEN\n";
    file.close();
    MetroSystem system;
    EXPECT_FALSE(
        system.loadNetwork("data/partially_numeric_distance.txt")
    );
}
TEST(PersistenceTest, RejectsPartiallyNumericStationId) {
    ofstream file("data/partially_numeric_station_id.txt");
    file << "#STATIONS\n";
    file << "12abc,Central,Blue,OPEN\n";
    file << "#CONNECTIONS\n";
    file.close();

    MetroSystem system;

    EXPECT_FALSE(
        system.loadNetwork("data/partially_numeric_station_id.txt")
    );
}
TEST(PersistenceTest, RejectsExtraStationFields) {
    ofstream file("data/extra_station_fields.txt");
    file << "#STATIONS\n";
    file << "1,Central,Blue,OPEN,EXTRA\n";
    file << "#CONNECTIONS\n";
    file.close();

    MetroSystem system;

    EXPECT_FALSE(
        system.loadNetwork("data/extra_station_fields.txt")
    );
}
TEST(PersistenceTest, RejectsUnknownStationConnection) {
    ofstream file("data/unknown_station.txt");
    file << "#STATIONS\n";
    file << "1,Central,Blue,OPEN\n";
    file << "#CONNECTIONS\n";
    file << "1,999,2.5,OPEN\n";
    file.close();
    MetroSystem system;
    EXPECT_FALSE(system.loadNetwork("data/unknown_station.txt"));
}
TEST(PersistenceTest, SaveLoadPreservesNetworkState) {
    MetroSystem original;
    original.addStation(Station(1, "Central", {"Blue"}, false));
    original.addStation(Station(2, "Market", {"Blue"}, false));
    original.addStation(Station(3, "Junction", {"Blue", "Red"}, true));
    original.addConnection(1, 2, 2.5);
    original.addConnection(2, 3, 3.0);
    original.closeStation(2);
    original.closeConnection(2, 3);
    ASSERT_TRUE(original.saveNetwork("data/test_roundtrip.txt"));
    MetroSystem loaded;
    ASSERT_TRUE(loaded.loadNetwork("data/test_roundtrip.txt"));
    Station* station = loaded.findStation(2);
    ASSERT_NE(station, nullptr);
    EXPECT_EQ(station->getStatus(), Status::CLOSED);
    bool connectionClosed = false;
    for (const auto& edge : loaded.listConnections()) {
        if ((edge.getFrom() == 2 && edge.getTo() == 3) ||
            (edge.getFrom() == 3 && edge.getTo() == 2)) {
            connectionClosed =
                edge.getStatus() == Status::CLOSED;
        }
    }
    EXPECT_TRUE(connectionClosed);
}