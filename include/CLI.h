#ifndef CLI_H
#define CLI_H

#include "MetroSystem.h"
#include "RouteResult.h"

class CLI {
private:
    MetroSystem& system;
    void showMenu() const;
    bool readInt(const string& prompt, int& value);
    bool readDouble(const string& prompt, double& value);
    bool readNonEmptyLine(const string& prompt, string& value);
    void printStation(const Station& station) const;
    void printRoute(const RouteResult& result) const;
    void handleViewStations();
    void handleSearchStation();
    void handleStationInfo();
    void handleMinimumStopsRoute();
    void handleShortestDistanceRoute();
    void handleCompareRoutes();
    void handleAddStation();
    void handleRemoveStation();
    void handleAddConnection();
    void handleRemoveConnection();
    void handleCloseStation();
    void handleReopenStation();
    void handleCloseConnection();
    void handleReopenConnection();
    void handleNetworkStatus();
    void handleSaveNetwork();
    void handleLoadNetwork();
    void handleDemo();
public:
    explicit CLI(MetroSystem& system);
    void run();
};
#endif