#ifndef TRABALHO2_PATH_H
#define TRABALHO2_PATH_H

#include <string>

using namespace std;

class Path {
public:
    Path(int stationA, int stationB, int capacity, string& service);
    int getStationA() const;
    int getStationB() const;
    int getCapacity() const;
    string getService() const;
    int getFlow() const;
    void setFlow(int flow);
    int getCost() const;

private:
    int stationA;
    int stationB;
    int capacity;
    int flow;
    string service;
    int costPerTrain;
    int cost;
};


#endif //TRABALHO2_PATH_H
