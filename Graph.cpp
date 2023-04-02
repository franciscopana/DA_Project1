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


bool Graph::bfs(int** residualGraph, int source, int sink, int parent[], int visited[]) {
    for(int i = 0; i < stations.size(); i++){
        visited[i] = false;
    }

    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(int v = 0; v < stations.size(); v++){
            if(visited[v] == false && residualGraph[u][v] > 0){
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return (visited[sink] == true);
}


int Graph::edmondsKarp(int source, int sink) {
    int** residualGraph = new int*[stations.size()];
    for(int i = 0; i < stations.size(); i++){
        residualGraph[i] = new int[stations.size()];
    }

    for(int i = 0; i < stations.size(); i++){
        for(int j = 0; j < stations.size(); j++){
            residualGraph[i][j] = 0;
        }
    }

    for(auto path : paths){
        residualGraph[path->getStationA()][path->getStationB()] = path->getCapacity();
    }

    int parent[stations.size()];
    int visited[stations.size()];

    int maxFlow = 0;

    while(bfs(residualGraph, source, sink, parent, visited)){
        int pathFlow = INT_MAX;
        for(int v = sink; v != source; v = parent[v]){
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        for(int v = sink; v != source; v = parent[v]){
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
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