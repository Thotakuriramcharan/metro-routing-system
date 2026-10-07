# Metro Routing System

A C++ metro route planning and network management system.

## Features

- Station management
- Connection management
- Open/closed station and connection states
- BFS minimum-stops routing
- Dijkstra shortest-distance routing
- Alternative route calculation when parts of the network are closed
- Network save/load persistence
- Validation of malformed network data
- GoogleTest-based testing

## Project Structure

```text
metro-routing-system/
├── data/
│   ├── metro_network.txt
│   └── mini_network.txt
├── include/
│   ├── Edge.h
│   ├── MetroGraph.h
│   ├── MetroSystem.h
│   ├── RouteEngine.h
│   ├── RouteResult.h
│   └── Station.h
├── src/
│   ├── Edge.cpp
│   ├── MetroGraph.cpp
│   ├── MetroSystem.cpp
│   ├── RouteEngine.cpp
│   ├── Station.cpp
│   └── main.cpp
├── tests/
│   ├── test_bfs.cpp
│   ├── test_connections.cpp
│   ├── test_dijkstra.cpp
│   ├── test_disruptions.cpp
│   ├── test_graph.cpp
│   ├── test_metro_system.cpp
│   ├── test_persistence.cpp
│   └── test_station.cpp
├── CMakeLists.txt
└── README.md