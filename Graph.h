/**
 * @file Graph.h
 * @brief This file contains the declaration of the Graph class.
 */

#ifndef TRABALHO2_GRAPH_H
#define TRABALHO2_GRAPH_H

#include <set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include "Station.h"
#include "Path.h"


/**
 * @brief The Graph class represents a graph.
 */
class Graph {
public:
    /**
     * @brief Constructs a Graph object.
     *
     * Time Complexity: O(1)
     */
    Graph();
<<<<<<< HEAD
    void setup();
    void reset();

    bool bfs(int source, int sink);
=======

    /**
     * @brief Adds all Stations to the graph from a CSV file
     *
     *
     * Time Complexity: O(n)
     */
    void addStations();

    /**
     * @brief Adds all Paths to the graph from a CSV file
     *
     *
     * Time Complexity: O(n)
     */
    void addPaths();


    /**
     * @brief Implements the Edmonds-Karp algorithm for maximum flow
     *
     * @param source The id of the source Station
     * @param sink The id of the sink Station
     * @return The maximum flow from source to sink
     *
     * Time Complexity: O(n^2)
     */
>>>>>>> doxygen
    int edmondsKarp(int source, int sink);

    /**
     * @brief Implements the Dijkstra algorithm for minimum cost flow
     *
     * @param source The id of the source Station
     * @param destination The id of the destination Station
     * @return The minimum cost flow from source to destination
     *
     * Time Complexity: O(n^2)
     */
    int dijkstra(int source,int destination);

<<<<<<< HEAD
=======
    /**
     * @brief Implements a breadth-first search to find a path from source to sink
     *
     * @param source The id of the source Station
     * @param sink The id of the sink Station
     * @return True if there exists a path from source to sink, false otherwise
     *
     * Time Complexity: O(n)
     */
    bool bfs(int source, int sink);

    /**
     * @brief Finds the minimum flow along a path from source to sink
     *
     * @param source The id of the source Station
     * @param sink The id of the sink Station
     * @return The minimum flow along the path from source to sink
     *
     * Time Complexity: O(n)
     */
>>>>>>> doxygen
    int findMinFlowAlongPath(int source, int sink);

    /**
     * @brief Updates the flow along a path from source to sink
     *
     * @param source The id of the source Station
     * @param sink The id of the sink Station
     * @param flow The new flow along the path
     *
     * Time Complexity: O(n)
     */
    void updateFlowAlongPath(int source, int sink, int flow);

    /**
     * @brief Gets all pairs of adjacent elements from a vector
     *
     * @param v The vector
     * @return A vector of all adjacent pairs
     *
     * Time Complexity: O(n)
     */
    vector<pair<int, int>> getPairs(vector<int> v);

    /**
     * @brief Calculates the total flow for a given set of paths
     *
     * @param v The set of paths
     * @return The total flow for the set of paths
     *
     * Time Complexity: O(n)
     */
    int calculateTotalFlow(const vector<int> &v);


    /**
     * @brief Gets the flow for all municipalities
     *
     * @return A vector of pairs containing the municipality name and its flow
     *
     * Time Complexity: O(n)
     */
    vector<pair<string, int>> flowsForAllMunicipalities();

    /**
     * @brief Gets the flow for all districts
     *
     * @return A vector of pairs containing the district name and its flow
     *
     * Time Complexity: O(n)
     */
    vector<pair<string, int>> flowsForAllDistricts();
<<<<<<< HEAD
    int maxSimultaneousArrivals(int id);
=======

    /**
     * @brief Gets the minimum capacity along a path from source to sink
     * @param source
     * @param sink
     * @return
     *
     * Time Complexity: O(n)
     */
>>>>>>> doxygen
    int getMinCapacityAlongPath(int source, int sink);

    /**
     * @brief Gets the cost for a path from source to destination
     * @param source
     * @param destination
     * @param flow
     * @return
     *
     * Time Complexity: O(n)
     */
    int getPathCost(int source, int destination, int flow);
    vector<pair<int, int>> maxPairs();
    vector<pair<Station*, int>> compareResults(vector<int> v1, vector<int> v2);

    /**
     * @brief Get the map of stations indexed by municipality.
     * @return
     *
     * Time Complexity: O(n)
     */
    map<string, vector<int>> getStationsByMunicipality() const;

    /**
     * @brief Get the map of municipalities indexed by district.
     * @return
     *
     * Time Complexity: O(n)
     */
    map<string, vector<string>> getMunicipalitiesByDistrict() const;

    /**
     * @brief Get the vector of districts.
     * @return
     *
     * Time Complexity: O(n)
     */
    vector<string> getDistricts() const;

    /**
     * @brief Get the vector of stations.
     * @return
     *
     * Time Complexity: O(n)
     */
    vector<Station*> getStations() const;

    /**
     * @brief Change the capacity of the given paths to the new capacities.
     * @param newCapacities
     * @return
     *
     * Time Complexity: O(n)
     */
    void changePathsCapacity(map<Path*, int> &newCapacities);

    /**
     * @brief Prints the path from source to destination.
     * @param source
     * @param destination
     *
     * Time Complexity: O(n)
     */
    void printPath(int source, int destination);

<<<<<<< HEAD
private:
    vector<Station*> stations;
    set<Path*> paths;
    map<string, vector<int>> stationsByMunicipality;
    map<string, vector<string>> municipalitiesByDistrict;
    vector<string> districts;

    void addStations();
    void addPaths();
    void setupSuperNode();

    void sortDistricts();
    void sortMunicipalities();

    void clear();
=======
    /**
     * @brief Resets the graph to its initial state.
     *
     * Time Complexity: O(n)
     */
    void reset();

private:
    vector<Station*> stations;/*List of stations in the graph*/
    set<Path*> paths; /*List of paths in the graph*/
    map<string, vector<int>> stationsByMunicipality; /*Map of stations indexed by municipality*/
    map<string, vector<string>> municipalitiesByDistrict; /*Map of municipalities indexed by district*/
    vector<string> districts; /*List of districts*/
    void sortDistricts(); /*Sorts the districts vector*/
    void sortMunicipalities(); /*Sorts the municipalities vector*/
>>>>>>> doxygen
};


#endif //TRABALHO2_GRAPH_H
