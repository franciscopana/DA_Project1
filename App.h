/**
 * @file App.h
 * @brief App class header file
 */

#ifndef TRABALHO2_APP_H
#define TRABALHO2_APP_H

#include "Graph.h"

using namespace std;

/**
 * @brief Class that represents the application
 */
class App {
public:
    /**
     * @brief Constructor of the class
     * @param graph Graph of the application
     */
    App(Graph& graph);

    /**
     * @brief Runs the application
     */
    void run();

private:
    Graph graph;/**< Graph of the application */

    int getOption();/**< Gets the option of the user */

    void printMenu();/**< Prints the menu */
    void printMenu2();/**< Prints the menu of task 2 */
    void printMenu3();/**< Prints the menu of task 3 */

    void task2();/**< Runs task 2 */
    void task3();/**< Runs task 3 */
    void task4();/**< Runs task 4 */

<<<<<<< HEAD
    void maxFlowBetweenTwoStations();
    void maxFlowPairs();
    void reduceConnectivity();
    void k_municipalities_with_max_flow();
    void k_districts_with_max_flow();
    void simultaneousArrivals();
    void minAmountBetweenTwoStations();

    Station* selectStation();

=======
    void maxFlowBetweenTwoStations();/**< Runs task 2.1 */
    void reduceConnectivity();/**< Runs task 4.1 */
    void k_municipalities_with_max_flow();/**< Runs task 4.2 */
    void k_districts_with_max_flow();/**< Runs task 4.3 */
    void minAmountBetweenTwoStations();/**< Runs task 3.1 */

    Station* selectStation();/**< Selects a station */
>>>>>>> doxygen
};


#endif //TRABALHO2_APP_H
