#include <queue>
#include "Graph.h"
#include "Path.h"

Graph::Graph() {
    this->stations = vector<Station*>();
    this->paths = set<Path*>();
}

void Graph::addStations() {
    ifstream file("../Data/stations.csv");

    if (!file.is_open()) {
        cout << "Error opening stations.csv" << endl;
        return;
    }
    file.ignore(1000, '\n');
    string line;

    int i = 0;
    while (getline(file, line)) {
        vector<string> row;
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            row.push_back(token);
        }
        row[4].erase(row[4].size() - 1);

        string name = row[0];
        string district = row[1];
        string municipality = row[2];
        string township = row[3];
        string line = row[4];


        Station* station = new Station(i++, name, district, municipality, township, line);
        stations.push_back(station);

        if(district.empty() || municipality.empty()) continue;
        if(municipalitiesByDistrict.find(district) == municipalitiesByDistrict.end()){
            vector<string> municipalities;
            municipalities.push_back(municipality);
            municipalitiesByDistrict[district] = municipalities;
            districts.push_back(district);
        } else {
            if(find(municipalitiesByDistrict[district].begin(), municipalitiesByDistrict[district].end(), municipality) == municipalitiesByDistrict[district].end()){
                municipalitiesByDistrict[district].push_back(municipality);
            }
        }

        if(stationsByMunicipality.find(municipality) == stationsByMunicipality.end()){
            vector<int> ids;
            ids.push_back(station->getId());
            stationsByMunicipality[municipality] = ids;
        } else {
            stationsByMunicipality[municipality].push_back(station->getId());
        }
    }
}

void Graph::addPaths() {
    ifstream file("../Data/network.csv");

    if (!file.is_open()) {
        cout << "Error opening network.csv" << endl;
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

        Path* path = new Path(stationA->getId(), stationB->getId(), stoi(row[2]), row[3]);
        paths.insert(path);
        stationA->addPath(path);
        stationB->addPath(path);
    }
    sortDistricts();
    sortMunicipalities();
}


int Graph::findMinFlowAlongPath(int source, int sink) {
    int minFlow = INT_MAX;
    int current = sink;
    while(current != source){
        Station* station = stations[current];
        int pred = station->getPred();
        Station* predStation = stations[pred];
        for(auto path : station->getPaths()){
            if(path->getStationA() == predStation->getId() || path->getStationB() == predStation->getId()){
                minFlow = min(minFlow, path->getCapacity() - path->getFlow());
                break;
            }
        }
        current = pred;
    }
    return minFlow;
}


bool Graph::bfs(int source, int sink) {
    for(auto station : stations){
        station->setVisited(false);
        station->setPred(-1);
        station->setDist(INT_MAX);
    }

    queue<Station*> q;
    q.push(stations[source]);
    stations[source]->setVisited(true);
    stations[source]->setDist(0);

    while(!q.empty()){
        Station* station = q.front();
        q.pop();

        for(auto path : station->getPaths()){
            int id = path->getStationA() == station->getId() ? path->getStationB() : path->getStationA();
            Station* adjStation = stations[id];
            if(!adjStation->isVisited() && path->getFlow() < path->getCapacity()){
                adjStation->setVisited(true);
                adjStation->setDist(station->getDist() + 1);
                adjStation->setPred(station->getId());
                q.push(adjStation);
            }
        }
    }
    return stations[sink]->isVisited();
}


int Graph::edmondsKarp(int source, int sink) {
    for(auto path: paths){
        path->setFlow(0);
        path->setReverseFlow(0);
    }
    while(bfs(source, sink)){
        int minFlow = findMinFlowAlongPath(source, sink);
        int current = sink;
        while(current != source){
            Station* station = stations[current];
            int pred = station->getPred();
            Station* predStation = stations[pred];
            for(auto path : station->getPaths()){
                if(path->getStationA() == predStation->getId() || path->getStationB() == predStation->getId()){
                    path->setFlow(path->getFlow() + minFlow);
                    path->setReverseFlow(path->getReverseFlow() - minFlow);
                    break;
                }
            }
            current = pred;
        }
    }
    int maxFlow = 0;
    for(auto path : stations[source]->getPaths()){
        maxFlow += path->getFlow();
    }
    return maxFlow;
}


map<string, vector<string>> Graph::getMunicipalitiesByDistrict() const {
    return municipalitiesByDistrict;
}

vector<string> Graph::getDistricts() const {
    return districts;
}

map<string, vector<int>> Graph::getStationsByMunicipality() const {
    return stationsByMunicipality;
}

vector<Station*> Graph::getStations() const {
    return stations;
}

void Graph::sortDistricts() {
    sort(districts.begin(), districts.end());
}

void Graph::sortMunicipalities() {
    for(auto& district : municipalitiesByDistrict){
        sort(district.second.begin(), district.second.end());
    }
}