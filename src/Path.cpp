/**
 * @file Path.cpp
 * @brief Path class implementation
 */

#include "Path.h"

/**
 * @brief Constructor of the class
 * @param stationA ID of the one of the stations
 * @param stationB ID of the one of the stations
 * @param capacity Capacity of the path
 * @param service Service of the path
 *
 * Time Complexity: O(1)
 */
Path::Path(int stationA, int stationB, int capacity, string& service) {
    this->stationA = stationA;
    this->stationB = stationB;
    this->capacity = capacity;
    this->service = service;
    if(service == "STANDARD") this->costPerTrain = 2;
    else if(service == "ALFA PENDULAR") this->costPerTrain = 4;
    else this->costPerTrain = INT_MAX;
    this->cost = this->capacity * this->costPerTrain;
}

/**
 * @brief Gets the ID of the first station
 * @return ID of the first station
 *
 * Time Complexity: O(1)
 */
int Path::getStationA() const {
    return stationA;
}

/**
 * @brief Gets the ID of the second station
 * @return ID of the second station
 *
 * Time Complexity: O(1)
 */
int Path::getStationB() const {
    return stationB;
}

/**
 * @brief Gets the capacity of the path
 * @return Capacity of the path
 *
 * Time Complexity: O(1)
 */
int Path::getCapacity() const {
    return capacity;
}

/**
 * @brief Gets the flow of the path
 * @return Flow of the path
 *
 * Time Complexity: O(1)
 */
int Path::getFlow() const {
    return flow;
}

/**
 * @brief Sets the flow of the path
 * @param flow Flow of the path
 *
 * Time Complexity: O(1)
 */
string Path::getService() const {
    return service;
}

/**
 * @brief Gets the maximum cost of the path
 * @return Maximum cost of the path
 *
 * Time Complexity: O(1)
 */
void Path::setFlow(int flow) {
    this->flow = flow;
}

/**
 * @brief Gets the maximum cost of the path
 * @return Maximum cost of the path
 *
 * Time Complexity: O(1)
 */
int Path::getMaxCost() const {
    return cost;
}

/**
 * @brief Sets the capacity of the path
 * @param capacity Capacity of the path
 *
 * Time Complexity: O(1)
 */
void Path::setCapacity(int capacity) {
    this->capacity = capacity;
}

/**
 * @brief Gets the cost per train of the path
 * @return Cost per train of the path
 *
 * Time Complexity: O(1)
 */
int Path::getCostPerTrain() const {
    return costPerTrain;
}
