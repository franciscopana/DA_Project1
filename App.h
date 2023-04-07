#ifndef TRABALHO2_APP_H
#define TRABALHO2_APP_H

#include "Graph.h"

using namespace std;

class App {
public:
    App(Graph& graph);
    void run();

private:
    Graph graph;

    int getOption();

    void printMenu();
    void printMenu2();
    void printMenu3();

    void task2();
    void task3();
    void task4();

    void maxFlowBetweenTwoStations();
    void maxFlowPairs();
    void reduceConnectivity();
    void k_municipalities_with_max_flow();
    void k_districts_with_max_flow();
    void minAmountBetweenTwoStations();

    Station* selectStation();

};


#endif //TRABALHO2_APP_H
