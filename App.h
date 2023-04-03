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

    void printMenu();
    void printMenu2();
    void printMenu3();
    void printMenu4();

    void task2();
    void task3();
    void task4();

    int getOption();
    void maxFlowBetweenTwoStations();

    Station* selectStation();
};


#endif //TRABALHO2_APP_H
