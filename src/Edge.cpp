#include "../include/Edge.h"
#include <stdexcept>

Edge::Edge(int f, int t, double d) {
    if (d <= 0) {
        throw std::invalid_argument("Distance must be greater than 0");
    }

    from = f;
    to = t;
    distanceKm = d;
    status = Status::OPEN;
}

int Edge::getFrom() const {
    return from;
}

int Edge::getTo() const {
    return to;
}

double Edge::getDistance() const {
    return distanceKm;
}

Status Edge::getStatus() const {
    return status;
}

void Edge::setClosed() {
    status = Status::CLOSED;
}

void Edge::setOpen() {
    status = Status::OPEN;
}