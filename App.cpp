/**
 * @file App.cpp
 * @brief App class implementation
 */

#include "App.h"

/**
 * @brief Constructor of the class
 * @param graph Graph of the application
 *
 * Time Complexity: O(1)
 */
App::App(Graph& graph) {
    this->graph = graph;
}

/**
 * @brief Gets the option of the user
 *
 * Time Complexity: O(1)
 */
int App::getOption(){
    int option;
    cout << "Option: ";
    cin >> option;
    while(cin.fail()){
        cin.clear();
        cin.ignore(256,'\n');
        cout << "Insert a number: ";
        cin >> option;
    }
    cout << endl;
    return option;
}

/**
 * @brief Print the Menu
 *
 * Time Complexity: O(1)
 */
void App::printMenu(){
    cout << "--------- Menu ---------" << endl;
    cout << "1 - Exit" << endl;
    cout << "2 - Basic Service Metrics" << endl;
    cout << "3 - Operation Cost Optimization" << endl;
    cout << "4 - Reliability and Sensitivity to Line Failures" << endl;
    cout << "5 - Reset Graph" << endl;
}

/**
 * @brief Print the second Menu
 *
 * Time Complexity: O(1)
 */
void App::printMenu2(){
    cout << "----------------- Basic Service Metrics ----------------" << endl;
    cout << "1 - Calculate the maximum number of trains that can simultaneously travel between two specific stations." << endl;
    cout << "2 - Determine, from all pairs of stations, which ones require the most amount of trains when taking full advantage of the existing network capacity." << endl;
    cout << "3 - Indicate where management should assign larger budgets for the purchasing and maintenance of trains." << endl;
    cout << "4 - Report the maximum number of trains that can simultaneously arrive at a given station, taking into consideration the entire railway grid." << endl;
    cout << "5 - Go back" << endl;
}

/**
 * @brief Task 2, handles option 2 from the main menu
 *
 * Time Complexity: O(k) where k is the complexity of the function called inside the switch case statements (either maxFlowBetweenTwoStations(), k_municipalities_with_max_flow() and k_districts_with_max_flow())
 */
void App::task2() {
    printMenu2();
    int option = getOption();
    switch (option){
        case 1:
            maxFlowBetweenTwoStations();
            break;
        case 2:
            maxFlowPairs();
            break;
        case 3:
            k_municipalities_with_max_flow();
            k_districts_with_max_flow();
            break;
        case 4:
            simultaneousArrivals();
            break;
        case 5:
            return;
        default:
            cout << "Invalid option" << endl;
            return;
    }
}

/**
 * @brief Print the third Menu
 *
 * Time Complexity: O(1)
 */
void App::printMenu3() {
    cout << "----------------- Operation Cost Optimization ----------------" << endl;
    cout << "1 - Calculate the maximum number of trains that can simultaneously travel between two specific stations with minimum cost." << endl;
    cout << "2 - Go back" << endl;
}

/**
 * @brief Task 3, handles option 3 from the main menu
 *
 * Time Complexity: O(k) where k is the complexity of the function called inside the switch case statements (either minAmountBetweenTwoStations() or just returning immediately)
 */
void App::task3() {
    printMenu3();
    int option = getOption();
    switch (option) {
        case 1:
            minAmountBetweenTwoStations();
            break;
        case 2:
            return;
        default:
            cout << "Invalid option" << endl;
            return;
    }
}

/**
 * @brief Task 4, handles option 4 from the main menu
 *
 * Time Complexity: O(1)
 */
void App::task4() {
    cout << "----------------- Reliability and Sensitivity to Line Failures ----------------" << endl;
    cout << "Do you want to see a report of the most affected stations? (y/n) ";
    char chooseReport;
    cin >> chooseReport;
    if(chooseReport == 'y' || chooseReport == 'Y'){
        vector<int> beforeResults;

        for(int i = 0; i < graph.getStations().size()-1; i++) {
            beforeResults.push_back(graph.maxSimultaneousArrivals(i));
        }

        reduceConnectivity();

        vector<int> afterResults;
        for(int i = 0; i < graph.getStations().size()-1; i++){
            afterResults.push_back(graph.maxSimultaneousArrivals(i));
        }

        vector<pair<Station*, int>> results = graph.compareResults(beforeResults, afterResults);
        cout << "Affected stations: " << endl;
        for(int i = 0; i < results.size(); i++){
            if(results[i].second >= 0) break;
            cout << results[i].first->getName() << ": " << results[i].second << " trains" << endl;
        }
    }
    else
        reduceConnectivity();
}

/**
 * @brief Calculates the minimum amount of trains required to travel between two stations with minimum cost
 *
 * Time Complexity: O(Elog(V)), where E is the number of edges in the graph and V is the number of vertices. This is because it uses Dijkstra's algorithm to find the shortest path between two stations, and the implementation of Dijkstra's algorithm in the Graph class has a time complexity of O(Elog(V))
 */
void App::minAmountBetweenTwoStations() {
    cout << ">> FIRST STATION: " << endl;
    Station* stationA = selectStation();
    while(stationA == nullptr){
        cout << ">> FIRST STATION: " << endl;
        stationA = selectStation();
    }
    stationA->print();
    cout << endl << ">> SECOND STATION: " << endl;
    Station* stationB = selectStation();
    while(stationB == nullptr){
        cout << endl << ">> SECOND STATION: " << endl;
        stationB = selectStation();
    }
    stationB->print();

    graph.dijkstra(stationA->getId(), stationB->getId());
    int maxFlow = graph.getMinCapacityAlongPath(stationA->getId(), stationB->getId());
    if(maxFlow == -1){
        cout << "There is no possible path between these two stations." << endl;
        return;
    }
    cout << endl << "The maximum number of trains that can go from " << stationA->getName() << " to " << stationB->getName() << " with minimum cost is " << maxFlow << endl;
    cout << "Path: ";
    graph.printPath(stationA->getId(), stationB->getId());
    cout << "The cost of this path is " << graph.getPathCost(stationA->getId(), stationB->getId(), maxFlow) << endl;
}


/**
 * @brief Calculates the maximum flow between two stations
 *
 * Time Complexity: O(EV^2), where E is the number of edges in the graph and V is the number of vertices. This is because it uses Edmonds-Karp algorithm to find the maximum flow between two stations, and the implementation of Edmonds-Karp algorithm in the Graph class has a time complexity of O(EV^2)
 */
void App::maxFlowBetweenTwoStations(){
    cout << ">> FIRST STATION: " << endl;
    Station* stationA = selectStation();
    while(stationA == nullptr){
        cout << ">> FIRST STATION: " << endl;
        stationA = selectStation();
    }
    stationA->print();
    cout << endl << ">> SECOND STATION: " << endl;
    Station* stationB = selectStation();
    while(stationB == nullptr){
        cout << endl << ">> SECOND STATION: " << endl;
        stationB = selectStation();
    }
    stationB->print();
    if(stationA->getId() == stationB->getId()){
        cout << "The same station was selected twice! Try again." << endl;
        return;
    }

    int maxFlow = graph.edmondsKarp(stationA->getId(), stationB->getId());
    cout << endl << "Maximum number of trains that can simultaneously travel between " << stationA->getName() << " and " << stationB->getName() << " is " << maxFlow << endl;
}

void App::maxFlowPairs(){
    cout << "Calculating ..." << endl;
    vector<pair<int, int>> maxPairs = graph.maxPairs();
    if(maxPairs.size() == 0) cout << "There's been an error. Try again" << endl;

    cout << "The connection that requires the most amount of trains is " << endl;

    for(pair<int, int> stationPair : maxPairs){
        cout << graph.getStations().at(stationPair.first)->getName() << " - " << graph.getStations().at(stationPair.second)->getName() << endl;
    }

    cout << "With a maximum of " << graph.edmondsKarp(maxPairs.at(0).first, maxPairs.at(0).second) << " trains\n" << endl;
}

/**
 * @brief reduces the connectivity of the graph by changing the edges capacity
 * @return
 *
 * Time Complexity: O(E), where E is the number of edges in the graph. This is because it iterates through all edges and removes them one by one.
 */
void App::reduceConnectivity() {
    int n;
    cout << "How many paths are affected? (0 to cancel) ";
    cin >> n;
    map<Path*, int> newCapacities;
    for(int i = 0; i < n; i++){
        cout << "\n>> Path " << i+1 << endl;
        cout << "From: " << endl;
        auto from = selectStation();

        while(from == nullptr){
            cout << "From: " << endl;
            from = selectStation();
        }

        if(from->getPaths().empty()){
            cout << "This station has no paths! Select another one." << endl;
            i--;
            continue;
        }

        vector<Path*> paths = from->getPaths();

        cout << "Select a path: " << endl;

        bool connectionToSuperNode = false;
        for(int j = 0; j < paths.size(); j++){
            Path* p = paths[j];
            Station* s1 = graph.getStations()[p->getStationA()];
            Station* s2 = graph.getStations()[p->getStationB()];
            Station* other = s1 == from ? s2 : s1;
            if(other->getName() == "SUPERNODE") {
                connectionToSuperNode = true;
                continue;
            }
            cout << j+1 << " - " << from->getName() << "  ->  " << other->getName() << "  (" << p->getService() << ")" << endl;
        }

        int maxOption = (connectionToSuperNode)? paths.size()-1 : paths.size();
        int option = getOption();
        while(option < 1 || option > maxOption){
            cout << "Invalid option! Try again." << endl;
            option = getOption();
        }

        Path* p = paths[option-1];

        int reducedCapacity;
        cout << "What's this path's capacity? ";
        cin >> reducedCapacity;
        while(reducedCapacity < 0 || reducedCapacity >= p->getCapacity()){
            cout << "Invalid value! Must be greater or equal than 0 and lower than " << p->getCapacity() << endl;
            cout << "What's this path's capacity? ";
            cin >> reducedCapacity;
            cout << endl;
        }
        newCapacities[p] = reducedCapacity;
    }
    graph.changePathsCapacity(newCapacities);
}


/**
 * @brief Displays the top k municipalities with the highest flow and suggests investing in maintenance and purchasing of trains.
 *
 * Time Complexity: O(M log N + M log M + k) where M is the number of edges and N is the number of vertices in the graph.
 */
void App::k_municipalities_with_max_flow() {
    auto flowByMunicipality = graph.flowsForAllMunicipalities();
    int k;
    cout << "How many municipalities do you want to see? ";
    cin >> k;
    while(k < 0 || k > flowByMunicipality.size()){
        cout << "Invalid value! Must be greater or equal than 0 and lower than " << flowByMunicipality.size() << endl;
        cout << "How many municipalities do you want to see? ";
        cin >> k;
        cout << endl;
    }

    cout << "These are the " << k << " municipalities which should spend more money on maintenance and purchasing of trains:" << endl;
    for(int i = 0; i < k; i++){
        cout << i+1 << " - " << flowByMunicipality[i].first  << "\t(total flow: " << flowByMunicipality[i].second << ")" << endl;
    }
}

/**
 * @brief Displays the top k districts and top k municipalities with the highest flow.
 *
 * Time Complexity: O(D log N + D log D + k) where D is the number of edges and N is the number of vertices in the graph.
 */
void App::k_districts_with_max_flow() {
    auto flowByDistrict = graph.flowsForAllDistricts();
    int k;
    cout << "How many districts do you want to see? ";
    cin >> k;
    while(k < 0 || k > flowByDistrict.size()){
        cout << "Invalid value! Must be greater or equal than 0 and lower than " << flowByDistrict.size() << endl;
        cout << "How many districts do you want to see? ";
        cin >> k;
        cout << endl;
    }

    cout << "These are the " << k << " districts which should spend more money on maintenance and purchasing of trains:" << endl;
    for(int i = 0; i < k; i++){
        cout << i+1 << " - " <<  flowByDistrict[i].first << "\t(total flow: " << flowByDistrict[i].second << ")" << endl;;
    }
}

void App::simultaneousArrivals(){
    cout << ">> CHOOSE A STATION: " << endl;
    Station* stationA = selectStation();
    while(stationA == nullptr){
        cout << ">> CHOOSE A STATION: " << endl;
        stationA = selectStation();
    }
    stationA->print();

    int maxArrivals = graph.maxSimultaneousArrivals(stationA->getId());
    cout << endl << "Maximum number of trains that can simultaneously arrive at " << stationA->getName() <<  " is " << maxArrivals << endl;
}

/**
 * @brief allows the user to select a station from a district and municipality
 * @return Station* A pointer to the selected station, or nullptr if the user wants to go back.
 *
 * Time Complexity: O(D + M + S), where D is the number of districts, M is the number of municipalities and S is the number of stations.
 */
Station* App::selectStation() {
    cout << "Select the district: " << endl;
    for (int i = 0; i < graph.getDistricts().size(); i++) {
        cout << i + 1 << " - " << graph.getDistricts()[i] << endl;
    }
    int option = getOption();
    string district = graph.getDistricts()[option - 1];

    cout << "Select the municipality: " << endl;
    cout << "0 - Go Back" << endl;
    for (int i = 0; i < graph.getMunicipalitiesByDistrict()[district].size(); i++) {
        cout << i + 1 << " - " << graph.getMunicipalitiesByDistrict()[district][i] << endl;
    }
    option = getOption();
    if(option == 0) return nullptr;
    string municipality = graph.getMunicipalitiesByDistrict()[district][option - 1];

    cout << "Select the station: " << endl;
    cout << "0 - Go Back" << endl;
    for (int i = 0; i < graph.getStationsByMunicipality()[municipality].size(); i++) {
        int id = graph.getStationsByMunicipality()[municipality][i];
        cout << i + 1 << " - " << graph.getStations()[id]->getName() << endl;
    }
    option = getOption();
    if(option == 0) return nullptr;
    int id = graph.getStationsByMunicipality()[municipality][option - 1];
    Station* station = graph.getStations()[id];
    return station;
}

/**
 * @brief Main function of the application. It adds stations and paths to the graph and displays a menu with different tasks.
 *
 * Time Complexity: O(S + M log N + T) where S is the number of stations, M is the number of edges and N is the number of vertices in the graph and T is the total time complexity of all the tasks combined.
 */
void App::run(){
    graph.setup();

    while (true){
        printMenu();
        int option = getOption();
        switch (option){
            case 1:
                return;
            case 2:
                task2();
                break;
            case 3:
                task3();
                break;
            case 4:
                task4();
                break;
            case 5:
                cout << "Resetting graph... ";
                graph.reset();
                cout << "Done!" << endl;
                break;
            default:
                cout << "Invalid option" << endl;
        }
    }
}

