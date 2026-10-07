# Design Decisions

## 1. Weighted Adjacency List

The metro network is represented using a weighted adjacency list.

This provides efficient access to the neighboring stations needed by BFS and Dijkstra's algorithm.

## 2. Separate Station and Edge Classes

Stations and connections are represented by separate classes.

This keeps station-specific data independent from connection-specific data and makes the system easier to maintain.

## 3. MetroGraph as the Routing Data Structure

`MetroGraph` manages the underlying network structure.

`RouteEngine` does not directly manage station or connection data. It receives a `MetroGraph` and performs routing on it.

## 4. Network State Filtering in `neighbours()`

Closed stations and connections are filtered inside:

```cpp
MetroGraph::neighbours()