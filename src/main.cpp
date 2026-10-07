#include <bits/stdc++.h>
using namespace std;
#include "../include/MetroSystem.h"
int main() {
    MetroSystem system;
    if (!system.loadNetwork("data/metro_network.txt")) {
        cout << "Could not load network" << endl;
        return 1;
    }
    cout << "Network loaded successfully" << endl;
    return 0;
}