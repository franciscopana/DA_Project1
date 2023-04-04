#ifndef DA_PROJECT1_STATION_H
#define DA_PROJECT1_STATION_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Path.h"

using namespace std;

class Station {
public:
    Station(int id, string& name, string& district, string& municipality, string& township, string& line);
    int getId() const;
    string getName() const;
    string getDistrict() const;
    string getMunicipality() const;
    string getTownship() const;
    string getLine() const;
    vector<Path*> getPaths() const;
    void addPath(Path* path);
    bool isVisited() const;
    void setVisited(bool v);
    Path* getPred() const;
    void setPred(Path* p);
    int getDist() const;
    void setDist(int d);

    void print() const;

private:
    int id;
    string name;
    string district;
    string municipality;
    string township;
    string line;
    vector<Path*> paths;
    bool visited;
    Path* pred;
    int dist;
};


#endif //DA_PROJECT1_STATION_H
