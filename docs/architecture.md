# System Architecture

## Overview

The Metro Routing System is organized into separate layers for data representation, graph management, routing algorithms, and system-level operations.

## Main Components

### Station

Represents a metro station.

Stores:

- Station ID
- Station name
- Metro lines
- Interchange information
- Open/closed status

### Edge

Represents a connection between two stations.

Stores:

- Source station
- Destination station
- Distance
- Open/closed status

Connections are treated as undirected in the metro network.

### MetroGraph

Maintains the metro network as a weighted adjacency list.

Responsibilities:

- Add and remove stations
- Add and remove connections
- Check station and connection existence
- Maintain closed stations
- Maintain connection states
- Provide neighboring stations to routing algorithms

Network-state filtering is performed inside `neighbours()`. This allows routing algorithms to remain independent of station and connection closures.

### RouteEngine

Contains the routing algorithms.

#### BFS

Finds a route with the minimum number of stops.

#### Dijkstra

Finds a route with the minimum total distance.

Both algorithms operate on the `MetroGraph` interface.

### MetroSystem

Provides higher-level system management.

Responsibilities:

- Station management
- Connection management
- Network state management
- Network persistence
- Validation of network data

`MetroSystem` uses `MetroGraph` internally.

## Persistence

Network data is stored in two sections:

```text
#STATIONS
id,name,lines,status

#CONNECTIONS
from,to,distance,status