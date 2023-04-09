/**
 * @file Graph.h
 * @brief This file contains the declaration of the Graph class.
 */

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
#include <limits>
#include "Station.h"
#include "Path.h"


/**
 * @brief The Graph class represents a graph.
 */
class Graph {
public:
    Graph();

    void setup();
    void reset();

    bool bfs(int source, int sink);
    int edmondsKarp(int source, int sink);
    int dijkstra(int source,int destination);
    int findMinFlowAlongPath(int source, int sink);
    void updateFlowAlongPath(int source, int sink, int flow);
    vector<pair<int, int>> getPairs(vector<int> v);
    int calculateTotalFlow(const vector<int> &v);
    vector<pair<string, int>> flowsForAllMunicipalities();
    vector<pair<string, int>> flowsForAllDistricts();
    int maxSimultaneousArrivals(int id);
    int getMinCapacityAlongPath(int source, int sink);
    int getPathCost(int source, int destination, int flow);
    vector<pair<int, int>> maxPairs();
    vector<pair<Station*, int>> compareResults(vector<int> v1, vector<int> v2);
    void changePathsCapacity(map<Path*, int> &newCapacities);

    map<string, vector<int>> getStationsByMunicipality() const;
    map<string, vector<string>> getMunicipalitiesByDistrict() const;
    vector<string> getDistricts() const;
    vector<Station*> getStations() const;
    void printPath(int source, int destination);

private:
    vector<Station*> stations;
    vector<Path*> paths;
    vector<Path*> superPaths;
    map<string, vector<int>> stationsByMunicipality;
    map<string, vector<string>> municipalitiesByDistrict;
    vector<string> districts;

    void addStations();
    void addPaths();
    void setupSuperNode();

    void sortDistricts();
    void sortMunicipalities();

    void clear();
};


#endif //TRABALHO2_GRAPH_H
