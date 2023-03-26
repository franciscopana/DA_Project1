#include "App.h"

App::App(Graph graph) {
    this->graph = graph;
}

void App::menu(){
    cout << "--------- Menu ---------" << endl;
    cout << "1 - Find max flow between two stations" << endl;
    cout << "2 - Stations with the max flow" << endl;
    cout << "3 - Exit" << endl;
}

int App::getOption(){
    int option;
    cout << "Option: ";
    cin >> option;
    cout << endl;
    return option;
}

void App::maxFlowBetweenTwoStations(){

    /*string stationA;
    string stationB;
    cin.ignore();

    cout << "Station A: ";
    getline(cin, stationA);
    cout << "Station B: ";
    getline(cin, stationB);
     */

    cout << ">> FIRST STATION: " << endl;
    Station* stationA = selectStation();
    cout << ">> SECOND STATION: " << endl;
    Station* stationB = selectStation();
    int maxFlow = graph.edmondsKarp(stationA->getId(), stationB->getId());


    cout << "Max flow between " << stationA->getName() << " and " << stationB->getName() << " is " << maxFlow << endl;
}

Station* App::selectStation() {
    cout << "Select the district: " << endl;
    for (int i = 0; i < graph.getDistricts().size(); i++) {
        cout << i + 1 << " - " << graph.getDistricts()[i] << endl;
    }
    int option = getOption();
    string district = graph.getDistricts()[option - 1];

    cout << "Select the municipality: " << endl;
    for (int i = 0; i < graph.getMunicipalitiesByDistrict()[district].size(); i++) {
        cout << i + 1 << " - " << graph.getMunicipalitiesByDistrict()[district][i] << endl;
    }
    option = getOption();
    string municipality = graph.getMunicipalitiesByDistrict()[district][option - 1];

    cout << "Select the station: " << endl;
    for (int i = 0; i < graph.getStationsByMunicipality()[municipality].size(); i++) {
        int id = graph.getStationsByMunicipality()[municipality][i];
        cout << i + 1 << " - " << graph.getStations()[id]->getName() << endl;
    }
    option = getOption();
    int id = graph.getStationsByMunicipality()[municipality][option - 1];
    Station* station = graph.getStations()[id];
    station->print();
    return station;
}

void App::run(){
    graph.addStations();
    graph.addPaths();

    while (true){
        menu();
        int option = getOption();
        switch (option){
            case 1:
                maxFlowBetweenTwoStations();
                break;
            case 2:
                selectStation();
                break;
            case 3:
                return;
            default:
                cout << "Invalid option" << endl;
        }
    }
}

