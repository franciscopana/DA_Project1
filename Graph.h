#ifndef TRABALHO2_GRAPH_H
#define TRABALHO2_GRAPH_H

#include <set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include "Station.h"
#include "Path.h"

class Graph {
public:
    Graph();
    void addStations();
    void addPaths();

private:
    set<Station*> stations;
    set<Path*> paths;
};


#endif //TRABALHO2_GRAPH_H
