# Metro Routing System

A C++20 metro route planning and network management system using graph data structures, BFS, Dijkstra, network-state management, persistence, GoogleTest, CTest, and runtime benchmarking.
## Overview

The system models a metro network as a weighted graph: stations are vertices, connections are weighted edges, and stations/connections can be `OPEN` or `CLOSED`. It supports minimum-stops routing with BFS, shortest-distance routing with Dijkstra, network disruptions, persistence, and an interactive CLI.

## Features

- Station add/remove/search/list and line-based listing
- Station validation, interchange status, open/close state
- Weighted connection add/remove/open/close
- Duplicate, self-connection, missing-station, and distance validation
- BFS minimum-stops routing
- Dijkstra shortest-distance routing
- Path reconstruction and route comparison
- Stop count, distance, estimated interchanges, and lines used
- Alternative routes after station/connection disruptions
- Network save/load with validation
- Interactive 19-option command-line interface
## Architecture

```text
CLI
 │
 ▼
MetroSystem
 │
 ▼
MetroGraph ── Station / Edge
 │
 ▼
RouteEngine ── BFS / Dijkstra
 │
 ▼
RouteResult
```

| Component | Responsibility |
|---|---|
| `Station` | Station data, lines, interchange/status |
| `Edge` | Connection endpoints, distance, status |
| `MetroGraph` | Weighted adjacency list and network state |
| `MetroSystem` | Management, validation, persistence |
| `RouteEngine` | BFS, Dijkstra, path reconstruction |
| `RouteResult` | Common routing result |
| `CLI` | Interactive interface |
## Data Structures

The graph uses a weighted adjacency list: `unordered_map<int, vector<Edge>>`. Other core structures include `unordered_map<int, Station>`, `unordered_set<int>`, a BFS queue, and a Dijkstra priority queue.
## Algorithms

### BFS — Minimum Stops

Explores the graph level by level and minimizes station-to-station transitions.

```text
Time:  O(V + E)
Space: O(V)
```

### Dijkstra — Shortest Distance

Uses connection weights and a priority queue to minimize total distance.

```text
Time: O((V + E) log V)
```

| Property | BFS | Dijkstra |
|---|---|---|
| Objective | Minimum stops | Minimum distance |
| Uses weights | No | Yes |
| Main structure | Queue | Priority queue |
| Complexity | O(V + E) | O((V + E) log V) |

Both algorithms reconstruct the final path and return a common `RouteResult`.

> **Interchange note:** connections do not store explicit line IDs, so interchange calculation is a station-based approximation using station line information.
## Network State & Disruptions

Stations and connections remain in the graph when closed. The routing engine filters closed elements during traversal, allowing the network to be reopened without rebuilding it. This supports station closures, connection closures, alternative routes, and unreachable-route detection.
## Persistence

Network files use two sections:

```text
#STATIONS
id,name,lines,status

#CONNECTIONS
from,to,distance,status
```

The loader validates malformed records, invalid/partially numeric values, unknown stations, and unexpected fields. Data is loaded into a temporary `MetroSystem` and replaces the active network only after successful validation.
## CLI

The application provides 19 operations:

```text
1 View stations       2 Search station      3 Station info
4 Minimum-stops route 5 Shortest-distance   6 Compare routes
7 Add station         8 Remove station      9 Add connection
10 Remove connection  11 Close station      12 Reopen station
13 Close connection   14 Reopen connection  15 Network status
16 Save network       17 Load network       18 Demonstration
19 Exit
```

All 19 operations have been manually smoke-tested.
## Testing

The project uses GoogleTest and CTest with **8 test suites and 37 individual test cases**.

| Suite | Focus |
|---|---|
| `test_station` | Station behavior |
| `test_graph` | Graph operations/connectivity |
| `test_metro_system` | Management/validation |
| `test_connections` | Connection management |
| `test_disruptions` | Closures/alternative routes |
| `test_bfs` | Minimum-stops routing |
| `test_dijkstra` | Shortest-distance routing |
| `test_persistence` | Save/load/malformed data |

Run all tests:

```powershell
ctest --test-dir build --output-on-failure
```

Verified result: **8/8 tests passed — 100% pass rate.**
## Benchmarking

`tests/benchmark.cpp` uses `std::chrono::steady_clock` over 1000 runs on the 51-station/54-connection network for route `10 -> 40`.

| Algorithm | Average Time |
|---|---:|
| BFS | 31.747 μs |
| Dijkstra | 62.374 μs |

Dijkstra was slower in this benchmark, consistent with its additional priority-queue work. These are machine-specific measurements, not universal performance guarantees.
## Complexity Summary

| Operation | Complexity |
|---|---|
| Station lookup | Average O(1) |
| Station insertion | Average O(1) |
| BFS | O(V + E) |
| Dijkstra | O((V + E) log V) |
## Project Structure

```text
metro-routing-system/
├── data/          # metro network datasets
├── docs/          # architecture and design decisions
├── include/       # headers
├── src/           # application and core implementation
├── tests/         # GoogleTest suites + benchmark
├── CMakeLists.txt
├── LICENSE
├── README.md
└── .gitignore
```
## Build & Run

### Requirements

- C++20-compatible compiler
- CMake 3.20+
- Git
- Internet connection for first GoogleTest download

### Build

```powershell
git clone https://github.com/Thotakuriramcharan/metro-routing-system.git
cd metro-routing-system
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

### Run

```powershell
.\build\metro.exe
```

### Test

```powershell
ctest --test-dir build --output-on-failure
```

### Benchmark

```powershell
g++ -std=c++20 tests/benchmark.cpp src/Station.cpp src/Edge.cpp src/MetroGraph.cpp src/MetroSystem.cpp src/RouteEngine.cpp -Iinclude -o benchmark
.\benchmark.exe
```
## Design Decisions

- **Weighted adjacency list:** suited to a sparse metro network and BFS/Dijkstra.
- **Layered design:** separates graph operations, network management, and routing.
- **State instead of removal:** closed elements can be reopened without rebuilding the graph.
- **Common `RouteResult`:** keeps BFS/Dijkstra results comparable.
- **Temporary load:** prevents malformed files from partially replacing the active network.
## Dataset

The full included network contains **51 stations and 54 connections**. A smaller fixture is available at `data/mini_network.txt`.
## Limitations

- Interchange calculation is approximate because connections do not store line IDs.
- Benchmarking currently focuses on the 51-station network rather than a large scalability study.
- The documented build workflow targets Windows/MinGW.
- Cross-platform CI is not yet included.
## Future Improvements

- Line-aware interchange routing
- Travel-time and transfer-aware routing
- Multi-size scalability benchmarks
- Larger synthetic network fixtures
- Stress/property-based tests
- GitHub Actions and cross-platform CI
- Static analysis and code coverage
- Graph/network visualization
- Improved CLI presentation and route export
## Technical Stack

**C++20 · STL · CMake · GoogleTest · CTest · `std::chrono` · Git · GitHub · MinGW/GCC**
## Project Status

Core routing, network management, disruption handling, persistence, CLI, testing, and benchmarking are implemented and verified.

**Current verification:** 8 test suites · 37 test cases · 100% CTest pass rate · 51 stations · 54 connections · 19 CLI operations
## License

See the `LICENSE` file for the project license.
