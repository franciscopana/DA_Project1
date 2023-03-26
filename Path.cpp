
#include "Path.h"

Path::Path(int stationA, int stationB, int capacity, string service) {
    this->stationA = stationA;
    this->stationB = stationB;
    this->capacity = capacity;
    this->service = service;
}

int Path::getStationA() const {
    return stationA;
}

int Path::getStationB() const {
    return stationB;
}

int Path::getCapacity() const {
    return capacity;
}

int Path::getFlow() const {
    return flow;
}

string Path::getService() const {
    return service;
}

int Path::setFlow(int flow) {
    this->flow = flow;
}