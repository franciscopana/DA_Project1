#include "Graph.h"

Graph::Graph() {
    this->stations = set<Station*>();
    this->paths = set<Path*>();
}

void Graph::addStations() {
    ifstream file("../Data/stations.csv");

    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    file.ignore(1000, '\n');
    string line;
    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            row.push_back(token);
        }
        row[4].erase(row[4].size() - 1);

        Station* station = new Station(row[0], row[1], row[2], row[3], row[4]);
        stations.insert(station);
    }
}

void Graph::addPaths() {
    ifstream file("../Data/network.csv");

    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    file.ignore(1000, '\n');
    string line;
    while (getline(file, line)){
        vector<string> row;
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            row.push_back(token);
        }
        row[3].erase(row[3].size() - 1);

        Station* stationA;
        Station* stationB;
        for(auto station : stations){
            if(station->getName() == row[0]){
                stationA = station;
            }
            if(station->getName() == row[1]){
                stationB = station;
            }
        }

        Path* path = new Path(stationA, stationB, stoi(row[2]), row[3]);
        paths.insert(path);
    }
}
