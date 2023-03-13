#ifndef TRABALHO2_PATH_H
#define TRABALHO2_PATH_H

#include <string>
#include "Station.h"

using namespace std;

class Path {
public:
    Path(Station* stationA, Station* stationB, int capacity, string service);
    Station* getStationA() const;
    Station* getStationB() const;
    int getCapacity() const;
    string getService() const;

private:
    Station* stationA;
    Station* stationB;
    int capacity;
    string service;
};


#endif //TRABALHO2_PATH_H
