#ifndef TRABALHO2_APP_H
#define TRABALHO2_APP_H

#include "Graph.h"

using namespace std;

class App {
public:
    App(Graph graph);
    void run();

private:
    Graph graph;

    void menu();
    int getOption();
    void maxFlowBetweenTwoStations();
};


#endif //TRABALHO2_APP_H
