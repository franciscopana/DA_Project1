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
    int getFlow() const;
    string getService() const;
    int setFlow(int flow);

private:
    int stationA;
    int stationB;
    int capacity;
    int flow;
    string service;
};


#endif //TRABALHO2_PATH_H
