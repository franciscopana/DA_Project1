/**
 * @file Path.h
 * @brief Path class header file
 */

#ifndef TRABALHO2_PATH_H
#define TRABALHO2_PATH_H

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Class that represents a connection between two stations
 */
class Path {
public:
    /**
     * @brief Constructor of the class
     * @param stationA ID of one of the stations
     * @param stationB ID of one of the stations
     * @param capacity Capacity of the path
     * @param service Type of service of the path
     *
     * Time Complexity: O(1)
     */
    Path(int stationA, int stationB, int capacity, string& service);

    /**
     * @brief Gets the ID of the first station
     * @return ID of the first station
     *
     * Time Complexity: O(1)
     */
    int getStationA() const;

    /**
     * @brief Gets the ID of the second station
     * @return ID of the second station
     *
     * Time Complexity: O(1)
     */
    int getStationB() const;

    /**
     * @brief Gets the capacity of the path
     * @return Capacity of the path
     *
     * Time Complexity: O(1)
     */
    int getCapacity() const;


    /**
     * @brief Sets the capacity of the path
     * @param capacity Capacity of the path
     *
     * Time Complexity: O(1)
     */
    void setCapacity(int capacity);

    /**
     * @brief Gets the service of the path
     * @return Service of the path
     *
     * Time Complexity: O(1)
     */
    string getService() const;

    /**
     * @brief Gets the flow of the path
     * @return Flow of the path
     *
     * Time Complexity: O(1)
     */
    int getFlow() const;

    /**
     * @brief Sets the flow of the path
     * @param flow Flow of the path
     *
     * Time Complexity: O(1)
     */
    void setFlow(int flow);

    /**
     * @brief Gets the maximum cost of the path (cost per train * capacity)
     * @return Maximum cost of the path
     *
     * Time Complexity: O(1)
     */
    int getMaxCost() const;

    /**
     * @brief Gets the cost per train of the path
     * @return Cost per train of the path
     *
     * Time Complexity: O(1)
     */
    int getCostPerTrain() const;

    /**
     * @brief prints the path's specifications
     *
     * Time Complexity: O(1)
     */
    void print() const;

private:
    int stationA; /**< ID of one of the stations */
    int stationB; /**< ID of the of the stations */
    int capacity; /**< Capacity of the path */
    int flow; /**< Flow of the path */
    string service; /**< Service of the path */
    int costPerTrain; /**< Cost per train of the path */
    int cost; /**< Maximum cost of the path */
};


#endif //TRABALHO2_PATH_H
