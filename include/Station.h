#ifndef STATION_H
#define STATION_H

#include <bits/stdc++.h>
#include "Edge.h"
using namespace std;

class Station {
private:
    int id;
    string name;
    vector<string> lines;
    bool isInterchange;
    Status status;

public:
    Station(int id, string name,
            vector<string> lines, bool isInterchange);

    int getId() const;
    string getName() const;
    vector<string> getLines() const;
    bool getIsInterchange() const;
    Status getStatus() const;

    void setOpen();
    void setClose();
};

#endif