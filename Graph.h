#ifndef TRABALHO2_GRAPH_H
#define TRABALHO2_GRAPH_H

#include <set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
#include "Station.h"
#include "Path.h"

class Graph {
public:
    Graph();
    void addStations();
    void addPaths();

    int edmondsKarp(int source, int sink);
    bool bfs(int source, int sink);
    int findMinFlowAlongPath(int source, int sink);
    void updateFlowAlongPath(int source, int sink, int flow);
    map<int, string> totalFlowByMunicipality();
    vector<pair<int, int>> getPairs(vector<int> v);

    map<string, vector<int>> getStationsByMunicipality() const;
    map<string, vector<string>> getMunicipalitiesByDistrict() const;
    vector<string> getDistricts() const;
    vector<Station*> getStations() const;
    void changePathsCapacity(map<Path*, int> &newCapacities);

private:
    vector<Station*> stations;
    set<Path*> paths;
    map<string, vector<int>> stationsByMunicipality;
    map<string, vector<string>> municipalitiesByDistrict;
    vector<string> districts;
    void sortDistricts();
    void sortMunicipalities();
};


#endif //TRABALHO2_GRAPH_H
