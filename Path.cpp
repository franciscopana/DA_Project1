
#include "Path.h"

Path::Path(int stationA, int stationB, int capacity, string service) {
    this->stationA = stationA;
    this->stationB = stationB;
    this->capacity = capacity;
    this->service = service;
    if(service == "STANDARD") this->costPerTrain = 2;
    else if(service == "ALFA") this->costPerTrain = 4;
    else this->costPerTrain = -1;
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

void Path::setFlow(int flow) {
    this->flow = flow;
}

void Path::setReverseFlow(int reverseFlow) {
    this->reverseFlow = reverseFlow;
}

int Path::getReverseFlow() const {
    return reverseFlow;
}

int Path::getCostPerTrain() const {
    return costPerTrain;
}