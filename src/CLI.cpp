#include "../include/CLI.h"

#include "../include/RouteEngine.h"

#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

CLI::CLI(MetroSystem& system)
    : system(system) {
}

void CLI::showMenu() const {
    cout << "\n========== METRO ROUTING SYSTEM ==========\n";
    cout << "1. View all stations\n";
    cout << "2. Search station\n";
    cout << "3. View station information\n";
    cout << "4. Find minimum-stops route\n";
    cout << "5. Find shortest-distance route\n";
    cout << "6. Compare routes\n";
    cout << "7. Add station\n";
    cout << "8. Remove station\n";
    cout << "9. Add connection\n";
    cout << "10. Remove connection\n";
    cout << "11. Close station\n";
    cout << "12. Reopen station\n";
    cout << "13. Close connection\n";
    cout << "14. Reopen connection\n";
    cout << "15. View network status\n";
    cout << "16. Save network\n";
    cout << "17. Load network\n";
    cout << "18. Run demo scenario\n";
    cout << "19. Exit\n";
    cout << "==========================================\n";
}

bool CLI::readInt(const string& prompt, int& value) {
    while (true) {
        cout << prompt;

        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return true;
        }

        if (cin.eof()) {
            return false;
        }

        cout << "Invalid input. Please enter an integer.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool CLI::readDouble(const string& prompt, double& value) {
    while (true) {
        cout << prompt;

        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return true;
        }

        if (cin.eof()) {
            return false;
        }

        cout << "Invalid input. Please enter a number.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool CLI::readNonEmptyLine(
    const string& prompt,
    string& value
) {
    while (true) {
        cout << prompt;
        getline(cin, value);

        if (cin.eof()) {
            return false;
        }

        if (!value.empty()) {
            return true;
        }

        cout << "Input cannot be empty.\n";
    }
}

void CLI::printStation(const Station& station) const {
    cout << "ID: " << station.getId() << '\n';
    cout << "Name: " << station.getName() << '\n';

    cout << "Lines: ";

    const auto lines = station.getLines();

    for (size_t i = 0; i < lines.size(); ++i) {
        if (i > 0) {
            cout << ", ";
        }

        cout << lines[i];
    }

    cout << '\n';

    cout << "Interchange: "
         << (station.getIsInterchange() ? "YES" : "NO")
         << '\n';

    cout << "Status: "
         << (station.getStatus() == Status::OPEN
                 ? "OPEN"
                 : "CLOSED")
         << '\n';
}

void CLI::printRoute(const RouteResult& result) const {
    if (!result.routeExists) {
        cout << "No valid route available under the current "
                "network conditions.\n";
        return;
    }

    cout << "Route type: " << result.routeType << '\n';

    cout << "Path: ";

    for (size_t i = 0; i < result.path.size(); ++i) {
        if (i > 0) {
            cout << " -> ";
        }

        cout << result.path[i];
    }

    cout << '\n';

    cout << "Stops: " << result.stops << '\n';

    if (result.totalDistanceKm >= 0) {
        cout << "Distance: "
             << result.totalDistanceKm
             << " km\n";
    }

    cout << "Interchanges: "
         << result.interchanges << '\n';

    if (!result.linesUsed.empty()) {
        cout << "Lines used: ";

        for (size_t i = 0; i < result.linesUsed.size(); ++i) {
            if (i > 0) {
                cout << ", ";
            }

            cout << result.linesUsed[i];
        }

        cout << '\n';
    }
}

void CLI::handleViewStations() {
    const auto stations = system.listStations();

    if (stations.empty()) {
        cout << "No stations available.\n";
        return;
    }

    cout << "\n========== STATIONS ==========\n";

    for (const auto& station : stations) {
        printStation(station);
        cout << "------------------------------\n";
    }
}

void CLI::handleSearchStation() {
    string query;

    if (!readNonEmptyLine("Enter station name: ", query)) {
        return;
    }

    const auto stations =
        system.searchStationsByName(query);

    if (stations.empty()) {
        cout << "No matching stations found.\n";
        return;
    }

    cout << "\n========== SEARCH RESULTS ==========\n";

    for (const auto& station : stations) {
        printStation(station);
        cout << "------------------------------------\n";
    }
}

void CLI::handleStationInfo() {
    int id;

    if (!readInt("Enter station ID: ", id)) {
        return;
    }

    Station* station = system.findStation(id);

    if (station == nullptr) {
        cout << "Station not found.\n";
        return;
    }

    cout << "\n========== STATION INFORMATION ==========\n";
    printStation(*station);
    cout << "=========================================\n";
}

void CLI::handleMinimumStopsRoute() {
    int source;
    int destination;

    if (!readInt("Enter source station ID: ", source)) {
        return;
    }

    if (!readInt("Enter destination station ID: ", destination)) {
        return;
    }

    RouteEngine engine;

    const RouteResult result =
        engine.minimumStopsRoute(
            system.getGraph(),
            source,
            destination
        );

    cout << "\n========== MINIMUM-STOPS ROUTE ==========\n";
    printRoute(result);
}

void CLI::handleShortestDistanceRoute() {
    int source;
    int destination;

    if (!readInt("Enter source station ID: ", source)) {
        return;
    }

    if (!readInt("Enter destination station ID: ", destination)) {
        return;
    }

    RouteEngine engine;

    const RouteResult result =
        engine.shortestDistanceRoute(
            system.getGraph(),
            source,
            destination
        );

    cout << "\n========== SHORTEST-DISTANCE ROUTE ==========\n";
    printRoute(result);
}

void CLI::handleCompareRoutes() {
    int source;
    int destination;

    if (!readInt("Enter source station ID: ", source)) {
        return;
    }

    if (!readInt("Enter destination station ID: ", destination)) {
        return;
    }

    RouteEngine engine;

    const RouteComparison comparison =
        engine.compareRoutes(
            system.getGraph(),
            source,
            destination
        );

    cout << "\n========== MINIMUM-STOPS ROUTE ==========\n";
    printRoute(comparison.bfsResult);

    cout << "\n========== SHORTEST-DISTANCE ROUTE ==========\n";
    printRoute(comparison.dijkstraResult);
}

void CLI::handleAddStation() {
    int id;
    string name;
    string lineInput;

    if (!readInt("Enter station ID: ", id)) {
        return;
    }

    if (!readNonEmptyLine("Enter station name: ", name)) {
        return;
    }

    if (!readNonEmptyLine(
            "Enter metro lines separated by |: ",
            lineInput)) {
        return;
    }

    vector<string> lines;
    string currentLine;

    stringstream ss(lineInput);

    while (getline(ss, currentLine, '|')) {
        if (!currentLine.empty()) {
            lines.push_back(currentLine);
        }
    }

    if (lines.empty()) {
        cout << "At least one metro line is required.\n";
        return;
    }

    bool isInterchange = lines.size() > 1;

    Station station(
        id,
        name,
        lines,
        isInterchange
    );

    if (system.addStation(station)) {
        cout << "Station added successfully.\n";
    } else {
        cout << "Could not add station. "
                "Check for duplicate ID or name.\n";
    }
}

void CLI::handleRemoveStation() {
    int id;

    if (!readInt("Enter station ID: ", id)) {
        return;
    }

    if (system.removeStation(id)) {
        cout << "Station removed successfully.\n";
    } else {
        cout << "Could not remove station.\n";
    }
}

void CLI::handleAddConnection() {
    int from;
    int to;
    double distance;

    if (!readInt("Enter source station ID: ", from)) {
        return;
    }

    if (!readInt("Enter destination station ID: ", to)) {
        return;
    }

    if (!readDouble("Enter distance in km: ", distance)) {
        return;
    }

    if (system.addConnection(from, to, distance)) {
        cout << "Connection added successfully.\n";
    } else {
        cout << "Could not add connection.\n";
    }
}

void CLI::handleRemoveConnection() {
    int from;
    int to;

    if (!readInt("Enter source station ID: ", from)) {
        return;
    }

    if (!readInt("Enter destination station ID: ", to)) {
        return;
    }

    if (system.removeConnection(from, to)) {
        cout << "Connection removed successfully.\n";
    } else {
        cout << "Could not remove connection.\n";
    }
}

void CLI::handleCloseStation() {
    int id;

    if (!readInt("Enter station ID: ", id)) {
        return;
    }

    if (system.closeStation(id)) {
        cout << "Station closed successfully.\n";
    } else {
        cout << "Could not close station.\n";
    }
}

void CLI::handleReopenStation() {
    int id;

    if (!readInt("Enter station ID: ", id)) {
        return;
    }

    if (system.reopenStation(id)) {
        cout << "Station reopened successfully.\n";
    } else {
        cout << "Could not reopen station.\n";
    }
}

void CLI::handleCloseConnection() {
    int from;
    int to;

    if (!readInt("Enter source station ID: ", from)) {
        return;
    }

    if (!readInt("Enter destination station ID: ", to)) {
        return;
    }

    if (system.closeConnection(from, to)) {
        cout << "Connection closed successfully.\n";
    } else {
        cout << "Could not close connection.\n";
    }
}

void CLI::handleReopenConnection() {
    int from;
    int to;

    if (!readInt("Enter source station ID: ", from)) {
        return;
    }

    if (!readInt("Enter destination station ID: ", to)) {
        return;
    }

    if (system.reopenConnection(from, to)) {
        cout << "Connection reopened successfully.\n";
    } else {
        cout << "Could not reopen connection.\n";
    }
}

void CLI::handleNetworkStatus() {
    const auto stations = system.listStations();
    const auto connections = system.listConnections();

    int openStations = 0;
    int closedStations = 0;

    for (const auto& station : stations) {
        if (station.getStatus() == Status::OPEN) {
            ++openStations;
        } else {
            ++closedStations;
        }
    }

    int openConnections = 0;
    int closedConnections = 0;

    for (const auto& edge : connections) {
        if (edge.getStatus() == Status::OPEN) {
            ++openConnections;
        } else {
            ++closedConnections;
        }
    }

    cout << "\n========== NETWORK STATUS ==========\n";
    cout << "Total stations: " << stations.size() << '\n';
    cout << "Open stations: " << openStations << '\n';
    cout << "Closed stations: " << closedStations << '\n';

    cout << "Total connections: "
         << connections.size() << '\n';

    cout << "Open connections: "
         << openConnections << '\n';

    cout << "Closed connections: "
         << closedConnections << '\n';

    cout << "====================================\n";
}

void CLI::handleSaveNetwork() {
    string filename;

    if (!readNonEmptyLine(
            "Enter file path to save network: ",
            filename)) {
        return;
    }

    if (system.saveNetwork(filename)) {
        cout << "Network saved successfully.\n";
    } else {
        cout << "Could not save network.\n";
    }
}

void CLI::handleLoadNetwork() {
    string filename;

    if (!readNonEmptyLine(
            "Enter file path to load network: ",
            filename)) {
        return;
    }

    if (system.loadNetwork(filename)) {
        cout << "Network loaded successfully.\n";
    } else {
        cout << "Could not load network.\n";
    }
}

void CLI::handleDemo() {
    cout << "\n========== DEMO SCENARIO ==========\n";

    cout << "\n1. Minimum-stops route: 10 -> 2\n";

    RouteEngine engine;

    RouteResult minimumStops =
        engine.minimumStopsRoute(
            system.getGraph(),
            10,
            2
        );

    printRoute(minimumStops);

    cout << "\n2. Shortest-distance route: 10 -> 2\n";

    RouteResult shortestDistance =
        engine.shortestDistanceRoute(
            system.getGraph(),
            10,
            2
        );

    printRoute(shortestDistance);

    cout << "\n3. Closing station 1...\n";

    if (system.closeStation(1)) {
        cout << "Station 1 closed.\n";
    } else {
        cout << "Could not close station 1.\n";
    }

    cout << "\n4. Route after disruption: 10 -> 2\n";

    RouteResult disruptedRoute =
        engine.shortestDistanceRoute(
            system.getGraph(),
            10,
            2
        );

    printRoute(disruptedRoute);

    cout << "\n5. Reopening station 1...\n";

    if (system.reopenStation(1)) {
        cout << "Station 1 reopened.\n";
    } else {
        cout << "Could not reopen station 1.\n";
    }

    cout << "==================================\n";
}

void CLI::run() {
    while (true) {
        showMenu();

        int choice;

        if (!readInt("Enter choice: ", choice)) {
            cout << "\nInput ended. Exiting...\n";
            break;
        }

        switch (choice) {
            case 1:
                handleViewStations();
                break;

            case 2:
                handleSearchStation();
                break;

            case 3:
                handleStationInfo();
                break;

            case 4:
                handleMinimumStopsRoute();
                break;

            case 5:
                handleShortestDistanceRoute();
                break;

            case 6:
                handleCompareRoutes();
                break;

            case 7:
                handleAddStation();
                break;

            case 8:
                handleRemoveStation();
                break;

            case 9:
                handleAddConnection();
                break;

            case 10:
                handleRemoveConnection();
                break;

            case 11:
                handleCloseStation();
                break;

            case 12:
                handleReopenStation();
                break;

            case 13:
                handleCloseConnection();
                break;

            case 14:
                handleReopenConnection();
                break;

            case 15:
                handleNetworkStatus();
                break;

            case 16:
                handleSaveNetwork();
                break;

            case 17:
                handleLoadNetwork();
                break;

            case 18:
                handleDemo();
                break;

            case 19:
                cout << "Exiting...\n";
                return;

            default:
                cout << "Invalid choice. Please select "
                        "an option from 1 to 19.\n";
        }
    }
}