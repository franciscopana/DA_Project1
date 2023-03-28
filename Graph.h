#ifndef TRABALHO2_GRAPH_H
#define TRABALHO2_GRAPH_H

#include <set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include "Station.h"
#include "Path.h"
#include <algorithm>

class Graph {
public:
    Graph();
    void addStations();
    void addPaths();
    int edmondsKarp(int source, int sink);
    bool bfs(int** residualGraph, int source, int sink, int parent[], int visited[]);
    map<string, vector<int>> getStationsByMunicipality() const;
    map<string, vector<string>> getMunicipalitiesByDistrict() const;
    vector<string> getDistricts() const;
    vector<Station*> getStations() const;

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