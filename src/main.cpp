#include<bits/stdc++.h>
using namespace std;
#include "../include/Edge.h"
#include "../include/Station.h"
int main(){
    vector<Station> stations = {
        Station(1, "Central", {"Blue"}, true),
        Station(2, "Airport", {"Blue"}, false),
        Station(3, "Park", {"Blue"}, false),
        Station(4, "Market", {"Red"}, true),
        Station(5, "University", {"Red"}, false)
    };
    unordered_map<int, int> idToIndex;
    for (size_t i = 0; i < stations.size(); i++) {
        idToIndex[stations[i].getId()] = i;
    }
    for (const auto& station : stations) {
        cout << station.getId() << " "
            << station.getName() << " "
            << station.getIsInterchange() << '\n';
    }
    Edge e1(1, 2, 3.5);
    Edge e2(2, 3, 1.8);
    Edge e3(3, 4, 2.4);
        cout << e1.getDistance() << endl;
        e1.setClosed();
    if (e1.getStatus() == Status::CLOSED) {
        cout << "Edge is closed" << endl;
    }
        e1.setOpen();
    if (e1.getStatus() == Status::OPEN) {
        cout << "Edge is open" << endl;
    }
}