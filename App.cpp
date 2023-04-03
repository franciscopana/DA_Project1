#include "App.h"

App::App(Graph& graph) {
    this->graph = graph;
}

int App::getOption(){
    int option;
    cout << "Option: ";
    cin >> option;
    cout << endl;
    return option;
}

void App::printMenu(){
    cout << "--------- Menu ---------" << endl;
    cout << "1 - Exit" << endl;
    cout << "2 - Basic Service Metrics" << endl;
    cout << "3 - Operation Cost Optimization" << endl;
    cout << "4 - Reliability and Sensitivity to Line Failures" << endl;
}

void App::printMenu2(){
    cout << "----------------- Basic Service Metrics ----------------" << endl;
    cout << "1 - Calculate the maximum number of trains that can simultaneously travel between two specific stations." << endl;
    cout << "2 - Determine, from all pairs of stations, which ones require the most amount of trains when taking full advantage of the existing network capacity." << endl;
    cout << "3 - Indicate where management should assign larger budgets for the purchasing and maintenance of trains." << endl;
    cout << "4 - Report the maximum number of trains that can simultaneously arrive at a given station, taking into consideration the entire railway grid." << endl;
    cout << "5 - Go back" << endl;
}

void App::task2() {
    printMenu2();
    int option = getOption();
    switch (option){
        case 1:
            maxFlowBetweenTwoStations();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            return;
        default:
            cout << "Invalid option" << endl;
            return;
    }
}

void App::printMenu3() {
    cout << "----------------- Operation Cost Optimization ----------------" << endl;
    cout << "1 - Calculate the maximum number of trains that can simultaneously travel between two specific stations with minimum cost." << endl;
    cout << "2 - Go back" << endl;
}

void App::task3() {
    printMenu3();
    int option = getOption();
    switch (option) {
        case 1:
            break;
        case 2:
            return;
        default:
            cout << "Invalid option" << endl;
            return;
    }
}

void App::printMenu4() {
    cout << "----------------- Reliability and Sensitivity to Line Failures ----------------" << endl;
    cout << "1 - Calculate the maximum number of trains that can simultaneously travel between two specific stations in a network of reduced connectivity." << endl;
    cout << "2 - Go back" << endl;
}

void App::task4() {
    printMenu4();
    int option = getOption();
    switch (option) {
        case 1:
            break;
        case 2:
            return;
        default:
            cout << "Invalid option" << endl;
            return;
    }
}

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

    int maxFlow = graph.edmondsKarp(stationA->getId(), stationB->getId());
    cout << endl << "Maximum number of trains that can simultaneously travel between " << stationA->getName() << " and " << stationB->getName() << " is " << maxFlow << endl;
}

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

void App::run(){
    graph.addStations();
    graph.addPaths();

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
            default:
                cout << "Invalid option" << endl;
        }
    }
}

