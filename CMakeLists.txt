cmake_minimum_required(VERSION 3.20)

project(MetroRoutingSystem)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(metro
    src/main.cpp
    src/Station.cpp
    src/Edge.cpp
    src/MetroGraph.cpp
    src/MetroSystem.cpp
    src/RouteEngine.cpp
)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

function(add_metro_test test_name test_source)
    add_executable(${test_name}
        ${test_source}
        src/Station.cpp
        src/Edge.cpp
        src/MetroGraph.cpp
        src/MetroSystem.cpp
        src/RouteEngine.cpp
    )

    target_include_directories(${test_name} PRIVATE include)

    target_link_libraries(${test_name}
        GTest::gtest_main
    )

    add_test(
        NAME ${test_name}
        COMMAND ${test_name}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endfunction()

add_metro_test(test_station tests/test_station.cpp)
add_metro_test(test_graph tests/test_graph.cpp)
add_metro_test(test_metro_system tests/test_metro_system.cpp)
add_metro_test(test_connections tests/test_connections.cpp)
add_metro_test(test_disruptions tests/test_disruptions.cpp)
add_metro_test(test_bfs tests/test_bfs.cpp)
add_metro_test(test_dijkstra tests/test_dijkstra.cpp)
add_metro_test(test_persistence tests/test_persistence.cpp)