/**
 * @file Graph.cpp
 * @brief Graph class implementation
 */

#include <queue>
#include <stack>
#include "Graph.h"
#include "Path.h"


/**
 * @brief Constructs a Graph object.
 *
 * Time Complexity: O(1)
 */
Graph::Graph() {
    this->stations = vector<Station*>();
    this->paths = set<Path*>();
}


/**
 * @brief Adds all Stations to the graph from a CSV file
 *
 *
 * Time Complexity: O(n)
 */
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


/**
 * @brief Adds all Paths to the graph from a CSV file
 *
 * Time Complexity: O(n)
 */
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


/**
 * @brief Implements a breadth-first search to find a path from source to sink
 *
 * @param source The id of the source Station
 * @param sink The id of the sink Station
 * @return True if there exists a path from source to sink, false otherwise
 *
 * Time Complexity: O(n)
 */
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

/**
 * @brief Finds the minimum flow along a path from source to sink
 *
 * @param source The id of the source Station
 * @param sink The id of the sink Station
 * @return The minimum flow along a path from source to sink
 *
 * Time Complexity: O(n)
 */
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

/**
 * @brief Updates the flow along a path from source to sink
 *
 * @param source The id of the source Station
 * @param sink The id of the sink Station
 * @param flow The flow to be added to the path
 *
 * Time Complexity: O(n)
 */
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

/**
 * @brief Implements the Edmonds-Karp algorithm for maximum flow
 *
 * @param source The id of the source Station
 * @param sink The id of the sink Station
 * @return The maximum flow from source to sink
 *
 * Time Complexity: O(n^2)
 */
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

<<<<<<< HEAD
vector<pair<int, int>> Graph::maxPairs(){
    vector<pair<int, int>> maxPairs;
    int maxFlow = INT_MIN;

    for(unsigned int origin = 0; origin < stations.size() - -2; origin++){
        for(unsigned int destination = origin + 1; destination < stations.size() - 1; destination++){
            int flow = edmondsKarp(origin, destination);
            if(flow > maxFlow){
                maxFlow = flow;
                maxPairs.clear();
                maxPairs.emplace_back(origin, destination);
            }
            else if(flow == maxFlow){
                maxPairs.emplace_back(origin, destination);
            }
        }
    }
    return maxPairs;
}

=======
/**
 * @brief Change the capacity of the given paths to the new capacities.
 * @param newCapacities
 * @return
 *
 * Time Complexity: O(n)
 */
>>>>>>> doxygen
void Graph::changePathsCapacity(map<Path *, int> &newCapacities) {
    map<Path*, int> oldCapacities;
    for(auto element : newCapacities){
        oldCapacities[element.first] = element.first->getCapacity();
        element.first->setCapacity(element.second);
    }
    newCapacities = oldCapacities;
}

/**
 * @brief Gets all pairs of adjacent elements from a vector
 *
 * @param v The vector
 * @return A vector of all adjacent pairs
 *
 * Time Complexity: O(n^2)
 */
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

/**
 * @brief Calculates the total flow for a given set of paths
 * @param v The set of paths
 * @return The total flow for the set of paths
 *
 * Time Complexity: O(n^2)
 */
int Graph::calculateTotalFlow(const vector<int> &v) {
    int flow = 0;
    vector<pair<int, int>> pairs = getPairs(v);
    for(auto pair : pairs){
        flow += edmondsKarp(pair.first, pair.second);
    }
    return flow;
}

/**
 * @brief Gets the flow for all municipalities
 * @return A vector of pairs containing the municipality name and its flow
 *
 * Time Complexity: O(n^2)
 */
vector<pair<string, int>> Graph::flowsForAllMunicipalities() {
    vector<pair<string, int>> result;
    for(auto& item : stationsByMunicipality){
        int totalFlow = calculateTotalFlow(item.second);
        result.emplace_back(item.first, totalFlow);
    }
    sort(result.begin(), result.end(), [](pair<string, int> &a, pair<string, int> &b){
        return a.second > b.second;
    });
    return result;
}

/**
 * @brief Gets the flow for all districts
 * @return A vector of pairs containing the district name and its flow
 *
 * Time Complexity: O(n^2)
 */
vector<pair<string, int>> Graph::flowsForAllDistricts() {
    vector<pair<string, int>> result;
    for(auto& item : municipalitiesByDistrict){
        vector<int> districtStations;
        for(auto &municipality : item.second){
            for(auto &station : stationsByMunicipality[municipality]){
                districtStations.push_back(station);
            }
        }
        int districtFlow = calculateTotalFlow(districtStations);
        result.emplace_back(item.first, districtFlow);
    }
    sort(result.begin(), result.end(), [](pair<string, int> &a, pair<string, int> &b){
        return a.second > b.second;
    });
    return result;
}

int Graph::maxSimultaneousArrivals(int id) {
    auto superNode = stations.back();
    bool hasDirectConnection = false;
    for(auto path : superNode->getPaths()){
        if(path->getStationA() == id || path->getStationB() == id){
            hasDirectConnection = true;
            path->setCapacity(0);
            break;
        }
    }
    int result = edmondsKarp(stations.back()->getId(), id);
    for(auto path : superNode->getPaths()){
        if(path->getStationA() == id || path->getStationB() == id){
            path->setCapacity(INT_MAX);
            break;
        }
    }
    return result;
}

// Definition of Compare struct for priority_queue
struct Compare {
    bool operator()(const Station* s1, const Station* s2) {
        return s1->getDist() > s2->getDist();
    }
};

/**
 * @brief Implements the Dijkstra algorithm for minimum cost flow
 * @param source The id of the source Station
 * @param destination The id of the destination Station
 * @return The minimum cost flow from source to destination
 *
 * Time Complexity: O(n^2)
 */
int Graph::dijkstra(int source, int destination) {
    for(auto station : stations){
        station->setVisited(false);
        station->setPred(nullptr);
        station->setDist(INT_MAX);
    }

    Station* src = stations[source];
    Station* dest = stations[destination];
    src->setDist(0);
    priority_queue<Station*, vector<Station*>, Compare> pq;
    pq.push(src);

    while(!pq.empty()){
        Station* currStation = pq.top();
        pq.pop();
        currStation->setVisited(true);

        for(Path* path : currStation->getPaths()){
            Station* neighbor = nullptr;
            if(path->getStationA() == currStation->getId()){
                neighbor = stations[path->getStationB()];
            } else {
                neighbor = stations[path->getStationA()];
            }

            if(!neighbor->isVisited() && path->getCapacity() > 0){
                int newDist = currStation->getDist() + path->getMaxCost();
                if(newDist < neighbor->getDist()){
                    neighbor->setDist(newDist);
                    neighbor->setPred(path);
                    pq.push(neighbor);
                }
            }
        }
    }
    return dest->getDist();
}


/**
 * @brief Prints the path from source to destination.
 * @param source
 * @param destination
 *
 * Time Complexity: O(n)
 */
void Graph::printPath(int source, int destination) {
    stack<int> path;
    int current = destination;
    while(current != source){
        path.push(current);
        Station* station = stations[current];
        Path* predPath = station->getPred();
        int predId = predPath->getStationA() == station->getId() ? predPath->getStationB() : predPath->getStationA();
        current = predId;
    }
    path.push(source);

    while(path.size() > 1){
        cout << stations[path.top()]->getName() << " -> ";
        path.pop();
    }
    cout << stations[path.top()]->getName() << endl;
}


/**
 * @brief Gets the minimum capacity along a path from source to sink
 * @param source
 * @param sink
 * @return
 *
 * Time Complexity: O(n)
 */
int Graph::getMinCapacityAlongPath(int source, int sink) {
    int minCapacity = INT_MAX;
    int current = sink;
    while(current != source){
        Station* station = stations[current];
        Path* predPath = station->getPred();
        if(predPath == nullptr)
            return -1;
        int predId = predPath->getStationA() == station->getId() ? predPath->getStationB() : predPath->getStationA();
        minCapacity = min(minCapacity, predPath->getCapacity());
        current = predId;
    }
    return minCapacity;
}


/**
 * @brief Gets the cost for a path from source to destination
 * @param source
 * @param destination
 * @param flow
 * @return
 *
 * Time Complexity: O(n)
 */
int Graph::getPathCost(int source, int destination, int flow) {
    int cost = 0;
    int current = destination;
    while(current != source){
        Station* station = stations[current];
        Path* predPath = station->getPred();
        int predId = predPath->getStationA() == station->getId() ? predPath->getStationB() : predPath->getStationA();
        cost += predPath->getCostPerTrain();
        current = predId;
    }
    return cost * flow;
}

/**
 * @brief Get the map of municipalities indexed by district.
 * @return
 *
 * Time Complexity: O(1)
 */
map<string, vector<string>> Graph::getMunicipalitiesByDistrict() const {
    return municipalitiesByDistrict;
}

/**
 * @brief Get the vector of districts.
 * @return
 *
 * Time Complexity: O(1)
 */
vector<string> Graph::getDistricts() const {
    return districts;
}

/**
 * @brief Get the map of stations indexed by municipality.
 * @return
 *
 * Time Complexity: O(1)
 */
map<string, vector<int>> Graph::getStationsByMunicipality() const {
    return stationsByMunicipality;
}

/**
 * @brief Get the vector of Stations.
 * @return
 *
 * Time Complexity: O(1)
 */
vector<Station*> Graph::getStations() const {
    return stations;
}

/**
 * @brief Sort the districts vector.
 * @return
 *
 * Time Complexity: O(nlogn)
 */
void Graph::sortDistricts() {
    sort(districts.begin(), districts.end());
}

/**
 * @brief Sort the municipalities vector.
 * @return
 *
 * Time Complexity: O(nlogn)
 */
void Graph::sortMunicipalities() {
    for(auto& district : municipalitiesByDistrict){
        sort(district.second.begin(), district.second.end());
    }
}

/**
 * @brief Resets the graph to its initial state.
 *
 * Time Complexity: O(n)
 */
void Graph::reset(){
    clear();
    setup();
}

void Graph::setup(){
    addStations();
    addPaths();
    sortDistricts();
    sortMunicipalities();
    setupSuperNode();
}

void Graph::setupSuperNode() {
    string name = "SUPERNODE";
    string emptyStr = "";
    auto superNode = new Station(stations.size(), name, emptyStr, emptyStr, emptyStr, emptyStr);
    stations.push_back(superNode);
    for(int i = 0; i < stations.size() - 1; i++){
        if(stations[i]->getPaths().size() == 1){
            Path* newPath = new Path(superNode->getId(), stations[i]->getId(), INT_MAX, emptyStr);
            stations[i]->addPath(newPath);
            paths.insert(newPath);
            superNode->addPath(newPath);
        }
    }
}

vector<pair<Station*,int>> Graph::compareResults(vector<int> v1, vector<int> v2) {
    vector<pair<Station*, int>> result;

    for(int i = 0; i < v1.size(); i++){
        result.emplace_back(stations[i], v2[i]-v1[i]);
    }

    sort(result.begin(), result.end(), [](pair<Station*, int> &a, pair<Station*, int> &b){
        return a.second < b.second;
    });

    return result;
}

void Graph::clear(){
    for(auto station : stations){
        delete station;
    }
    for(auto path : paths){
        delete path;
    }

    stationsByMunicipality.clear();
    stations.clear();
    paths.clear();
    municipalitiesByDistrict.clear();
    districts.clear();
}