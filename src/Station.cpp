#include "../include/Station.h"
#include <stdexcept>

Station::Station(
    int id,
    string name,
    vector<string> lines,
    bool isInterchange
) {
    if (name.empty()) {
        throw invalid_argument("Station name cannot be empty");
    }

    this->id = id;
    this->name = name;
    this->lines = lines;
    this->isInterchange = isInterchange;
    this->status = Status::OPEN;
}

int Station::getId() const {
    return id;
}

string Station::getName() const {
    return name;
}

vector<string> Station::getLines() const {
    return lines;
}

bool Station::getIsInterchange() const {
    return isInterchange;
}

Status Station::getStatus() const {
    return status;
}

void Station::setOpen() {
    status = Status::OPEN;
}

void Station::setClose() {
    status = Status::CLOSED;
}