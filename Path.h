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
    void setFlow(int flow);
    void setReverseFlow(int reverseFlow);
    int getReverseFlow() const;
    int getCostPerTrain() const;

private:
    int stationA;
    int stationB;
    int capacity;
    int flow;
    int reverseFlow;
    string service;
    int costPerTrain;
};


#endif //TRABALHO2_PATH_H
