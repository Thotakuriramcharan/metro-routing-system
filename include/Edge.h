#ifndef EDGE_H
#define EDGE_H

enum class Status {
    OPEN,
    CLOSED
};

class Edge {
private:
    int from;
    int to;
    double distanceKm;
    Status status;

public:
    Edge(int f, int t, double d);

    int getFrom() const;
    int getTo() const;
    double getDistance() const;
    Status getStatus() const;

    void setClosed();
    void setOpen();
};

#endif