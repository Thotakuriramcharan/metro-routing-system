# Design Decisions

## 1. Why an Adjacency List?

The metro network is represented using a weighted adjacency list.

A metro network is relatively sparse: each station connects to only a small number of other stations compared with the total number of stations. An adjacency list therefore stores only the connections that actually exist.

I chose this instead of an adjacency matrix because an adjacency matrix would require O(V²) storage even when most station pairs are not directly connected.

The adjacency list also works naturally with BFS and Dijkstra because both algorithms need to iterate over the neighbours of a station.

---

## 2. Why BFS for Minimum Stops?

BFS was chosen for minimum-stops routing because every connection represents one station-to-station transition.

BFS explores the graph level by level:

- Level 0: source station
- Level 1: stations reachable in one stop
- Level 2: stations reachable in two stops
- and so on

Therefore, the first time BFS reaches the destination, it has found a route with the minimum number of stops.

BFS runs in O(V + E) using the adjacency-list representation.

Dijkstra was not necessary for this objective because connection distance is not used when minimizing the number of stops.

---

## 3. Why Dijkstra for Minimum Distance?

Dijkstra was chosen for shortest-distance routing because metro connections have different distances.

BFS treats every connection as having equal cost, so it cannot determine the route with the smallest total distance when edge weights differ.

Dijkstra maintains the currently known shortest distance to each station and repeatedly processes the station with the smallest tentative distance using a priority queue.

With the current adjacency-list implementation and priority queue, the complexity is:

O((V + E) log V)

---

## 4. Why Separate MetroGraph and RouteEngine?

`MetroGraph` is responsible for representing and manipulating the network structure.

`RouteEngine` is responsible for routing algorithms such as BFS and Dijkstra.

Separating them keeps responsibilities clear:

- `MetroGraph` → stations, connections, adjacency structure, network state
- `RouteEngine` → route calculation and path reconstruction

An alternative would have been to place BFS and Dijkstra directly inside `MetroGraph`, but that would mix graph representation with algorithm-specific routing logic.

Keeping the classes separate also makes it easier to add or modify routing algorithms later.

---

## 5. Why Files Instead of a Database?

The project uses text files for network persistence.

The main reason is the scale and purpose of this project. The network is a relatively small static dataset, and the project is intended to demonstrate C++ data structures, graph algorithms, validation, testing, and software engineering rather than database management.

A database would introduce additional infrastructure and complexity without providing a significant benefit for the current use case.

The file format also makes the network data easy to inspect and modify manually.

For a much larger production system with concurrent updates, persistent queries, authentication, and multiple users, a database would become more appropriate.

---

## 6. Why CLI Instead of a Web Interface?

The project uses an interactive command-line interface because the primary goal is to demonstrate the underlying C++ system.

The CLI provides a simple way to:

- inspect stations
- search stations
- calculate routes
- compare BFS and Dijkstra
- simulate disruptions
- save and load the network

Building a web interface would require additional frontend and backend infrastructure that is outside the main learning objectives of this project.

The CLI keeps the presentation layer lightweight while allowing the core C++ architecture to remain the focus.

---

## 7. Why GoogleTest?

GoogleTest was selected because the project contains several independent components that benefit from automated testing.

The test suite covers areas including:

- stations
- graph operations
- connections
- BFS
- Dijkstra
- network disruptions
- persistence

Using GoogleTest makes individual behaviors easy to verify and allows the full test suite to be executed automatically through CTest.

This is more reliable than manually testing the CLI every time a change is made.

---

## 8. Why CMake?

CMake was chosen to provide a reproducible build system.

The project contains multiple source files, GoogleTest integration, and several test executables. Compiling every source file manually would become inconvenient and error-prone.

CMake handles:

- C++ standard configuration
- source compilation
- GoogleTest integration
- test executable creation
- CTest registration

It also makes the project easier for another developer to configure and build from a fresh clone.

---

## 9. Why Explicit OPEN/CLOSED State?

Stations and connections are not physically removed when they are closed.

Instead, they maintain an explicit `OPEN` or `CLOSED` state.

This was chosen because a disruption should be reversible.

For example:

Open station
     ↓
Close station
     ↓
Routing ignores station
     ↓
Reopen station
     ↓
Routing can use station again

Physically removing a station or connection would make reopening more complicated and could require reconstructing part of the network.

Keeping the object in the graph while changing its state also makes disruption simulation easier to test.

---

## 10. What Would Change at 100,000+ Stations?

The current architecture is suitable for the project's current network size, but a much larger network would require additional engineering.

Potential changes would include:

- more careful memory management
- more efficient input/output and persistence
- stronger profiling and benchmarking
- optimized graph storage
- faster station lookup and indexing
- potentially preprocessing or specialized routing techniques
- more scalable persistence infrastructure
- additional performance and load testing

The current adjacency-list representation would still be a reasonable starting point for a sparse metro network, but the implementation would need to be profiled before choosing specific optimizations.

The important principle would be to measure the actual bottlenecks rather than prematurely optimizing the system.