#include<bits/stdc++.h>
using namespace std;
struct StationDraft {
    int id;
    std::string name;
    bool isInterchange;
};
struct EdgeDraft {
    int from;
    int to;
    double distanceKm;
};
void printStation(const StationDraft& s) {
    std::cout << s.id << " "
              << s.name << " "
              << s.isInterchange << '\n';
}
bool isValidDistance(int d) {
    return d > 0;
}
int main(){
    vector<StationDraft> stations = {
        {1, "Central", true},
        {2, "Airport", false},
        {3, "Park", false},
        {4, "Market", true},
        {5, "University", false}
    };
    unordered_map<int, int> idToIndex;
    for (int i = 0; i < stations.size(); i++) {
        idToIndex[stations[i].id] = i;
    }
    for (const auto& station : stations) {
        printStation(station);
    }
}