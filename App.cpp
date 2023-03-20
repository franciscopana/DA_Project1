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
    return option;
}

void App::maxFlowBetweenTwoStations(){
    string stationA;
    string stationB;
    cin.ignore();

    cout << "Station A: ";
    getline(cin, stationA);
    cout << "Station B: ";
    getline(cin, stationB);

    // call graph....()

    cout << "Max flow between " << stationA << " and " << stationB << " is " << endl;
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
                break;
            case 3:
                return;
            default:
                cout << "Invalid option" << endl;
        }
    }
}