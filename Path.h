#ifndef TRABALHO2_PATH_H
#define TRABALHO2_PATH_H

#include <string>

using namespace std;

class Path {
public:
    Path(int stationA, int stationB, int capacity, string service);
    int getStationA() const;
    int getStationB() const;
    int getCapacity() const;
    string getService() const;

private:
    int stationA;
    int stationB;
    int capacity;
    string service;
};


#endif //TRABALHO2_PATH_H
