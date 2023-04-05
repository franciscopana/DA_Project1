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

bool Graph::bfs(int source, int sink) {
    for(auto station : stations){
        station->setVisited(false);
        station->setPred(nullptr);
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
                adjStation->setPred(path);
                q.push(adjStation);
            }
        }
    }
    return stations[sink]->isVisited();
}


int Graph::findMinFlowAlongPath(int source, int sink) {
    int minFlow = INT_MAX;
    int current = sink;
    while(current != source){
        Station* station = stations[current];
        Path* predPath = station->getPred();
        minFlow = min(minFlow, predPath->getCapacity() - predPath->getFlow());
        int predId = predPath->getStationA() == station->getId() ? predPath->getStationB() : predPath->getStationA();
        current = predId;
    }
    return minFlow;
}

void Graph::updateFlowAlongPath(int source, int sink, int flow) {
    int current = sink;
    while(current != source){
        Station* station = stations[current];
        Path* predPath = station->getPred();
        predPath->setFlow(predPath->getFlow() + flow);
        int predId = predPath->getStationA() == station->getId() ? predPath->getStationB() : predPath->getStationA();
        current = predId;
    }
}


int Graph::edmondsKarp(int source, int sink) {
    for(auto path: paths){
        path->setFlow(0);
    }
    while(bfs(source, sink)){
        int minFlow = findMinFlowAlongPath(source, sink);
        updateFlowAlongPath(source, sink, minFlow);
    }
    int maxFlow = 0;
    for(auto path : stations[source]->getPaths()){
        maxFlow += path->getFlow();
    }
    return maxFlow;
}

void Graph::changePathsCapacity(map<Path *, int> &newCapacities) {
    map<Path*, int> oldCapacities;
    for(auto element : newCapacities){
        oldCapacities[element.first] = element.first->getCapacity();
        element.first->setCapacity(element.second);
    }
    newCapacities = oldCapacities;
}

vector<pair<int, int>> Graph::getPairs(vector<int> v){
    vector<pair<int, int>> result;
    for (int i = 0; i < v.size(); i++) {
        for (int j = i + 1; j < v.size(); j++) {
            pair<int, int> currentPair = make_pair(v[i], v[j]);
            if (find(result.begin(), result.end(), currentPair) == result.end()) {
                result.push_back(currentPair);
            }
        }
    }
    return result;
}

map<int, string> Graph::totalFlowByMunicipality() {
    map<int , string> result;
    for(auto& item : stationsByMunicipality){
        int totalFlow = 0;
        vector<pair<int, int>> pairs = getPairs(item.second);
        for(auto pair : pairs){
            totalFlow += edmondsKarp(pair.first, pair.second);
        }
        result[totalFlow] = item.first;
    }
    return result;
}
// Definition of Compare struct for priority_queue
struct Compare {
    bool operator()(const Station* s1, const Station* s2) {
        return s1->getDist() > s2->getDist();
    }
};

int Graph::dijkstra(const Station& source, const Station& destination) {
    for(auto station : stations){
        station->setVisited(false);
        station->setPred(nullptr);
        station->setDist(INT_MAX);
    }

    Station* src = const_cast<Station*>(&source); // Remove costness for setting distance
    src->setDist(0);
    priority_queue<Station*, vector<Station*>, Compare> pq;
    pq.push(const_cast<Station*>(&source));

    while(!pq.empty() && !destination.isVisited()){
        Station* currStation = pq.top();
        pq.pop();
        currStation->setVisited(true);

        if(currStation == &destination){
            break;
        }

        for(Path* path : currStation->getPaths()){
            Station* neighbor = nullptr;
            if(path->getStationA() == currStation->getId()){
                neighbor = stations[path->getStationB()];
            } else {
                neighbor = stations[path->getStationA()];
            }

            if(!neighbor->isVisited()){
                int newDist = currStation->getDist() + path->getCost();
                if(newDist < neighbor->getDist()){
                    neighbor->setDist(newDist);
                    neighbor->setPred(path);
                    pq.push(neighbor);
                }
            }
        }
    }
    int maxAmount = 0;
    const Station* currStation = &destination;
    while(currStation != nullptr && currStation->getPred() != nullptr){
        maxAmount += 1;
        currStation = stations[currStation->getPred()->getStationA()] == currStation ? stations[currStation->getPred()->getStationB()] : stations[currStation->getPred()->getStationA()];
    }
    return maxAmount;
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