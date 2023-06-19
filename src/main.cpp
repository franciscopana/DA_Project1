/**
 * @file main.cpp
 * @brief Main file for the project
 */

#include "App.h"

/**
 * @brief Main function
 * @return 0
 *
 * Time Complexity: O(1)
 */
int main() {
    Graph graph = Graph();
    App app = App(graph);
    app.run();
    return 0;
}