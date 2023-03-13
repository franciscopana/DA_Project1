
#include "Path.h"

Path::Path(Station* stationA, Station* stationB, int capacity, string service) {
    this->stationA = stationA;
    this->stationB = stationB;
    this->capacity = capacity;
    this->service = service;
}

Station* Path::getStationA() const {
    return stationA;
}

Station* Path::getStationB() const {
    return stationB;
}

int Path::getCapacity() const {
    return capacity;
}

string Path::getService() const {
    return service;
}
