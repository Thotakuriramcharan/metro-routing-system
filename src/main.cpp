#include <iostream>
#include "../include/CLI.h"
int main() {
    MetroSystem system;
    if (!system.loadNetwork("data/metro_network.txt")) {
        std::cout << "Could not load network\n";
        return 1;
    }
    CLI cli(system);
    cli.run();
    return 0;
}