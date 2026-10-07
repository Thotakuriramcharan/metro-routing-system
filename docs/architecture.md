# Architecture

## System Flow

```text
CLI
 ↓
MetroSystem
 ↓
MetroGraph + RouteEngine
 ↓
BFS / Dijkstra
 ↓
Path Reconstruction
 ↓
RouteResult

Components
- CLI — Handles user input and displays results.
- MetroSystem — Manages stations, connections, disruptions, and persistence.
- MetroGraph — Stores the metro network using an adjacency list.
- RouteEngine — Implements BFS and Dijkstra routing.
- RouteResult — Stores the calculated route and its details.
Routing
- BFS → minimum stops
- Dijkstra → shortest distance
Network State
Stations and connections use OPEN / CLOSED states. Closed components are ignored during routing.
Persistence
Network data is saved and loaded using text files containing station, connection, distance, and status information.
Design Principle
The system separates user interaction, network management, graph representation, and routing logic so that each component has a clear responsibility.