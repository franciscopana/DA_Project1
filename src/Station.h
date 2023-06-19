/**
 * @file Station.h
 * @brief This file contains the declaration of the Station class.
 */

#ifndef DA_PROJECT1_STATION_H
#define DA_PROJECT1_STATION_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Path.h"

using namespace std;

/**
 * @brief The Station class represents a station in a transportation network.
 */
class Station {
public:
    /**
     * @brief Constructs a Station object.
     * @param id The ID of the station.
     * @param name The name of the station.
     * @param district The district where the station is located.
     * @param municipality The municipality where the station is located.
     * @param township The township where the station is located.
     * @param line The line on which the station is located.
     *
     * Time Complexity: O(1)
     */
    Station(int id, string& name, string& district, string& municipality, string& township, string& line);

    /**
     * @brief Gets the ID of the station.
     * @return The ID of the station.
     *
     * Time Complexity: O(1)
     */
    int getId() const;


    /**
     * @brief Gets the name of the station.
     * @return The name of the station.
     *
     * Time Complexity: O(1)
     */
    string getName() const;

    /**
     * @brief Gets the district where the station is located.
     * @return The district where the station is located.
     *
     * Time Complexity: O(1)
     */
    string getDistrict() const;

    /**
     * @brief Gets the municipality where the station is located.
     * @return The municipality where the station is located.
     *
     * Time Complexity: O(1)
     */
    string getMunicipality() const;

    /**
     * @brief Gets the township where the station is located.
     * @return The township where the station is located.
     *
     * Time Complexity: O(1)
     */
    string getTownship() const;

    /**
     * @brief Gets the line on which the station is located.
     * @return The line on which the station is located.
     *
     * Time Complexity: O(1)
     */
    string getLine() const;

    /**
     * @brief Gets the paths which are connected to this station.
     * @return The paths connected to this station.
     *
     * Time Complexity: O(1)
     */
    vector<Path*> getPaths() const;

    /**
     * @brief Adds a path connected to this station.
     * @param path The path to add.
     *
     * Time Complexity: O(1)
     */
    void addPath(Path* path);

    /**
     * @brief Checks whether the station has been visited.
     * @return True if the station has been visited, false otherwise.
     *
     * Time Complexity: O(1)
     */
    bool isVisited() const;

    /**
     * @brief Sets whether the station has been visited.
     * @param v Whether the station has been visited.
     *
     * Time Complexity: O(1)
     */
    void setVisited(bool v);

    /**
     * @brief Gets the predecessor path of this station.
     * @return The predecessor path of this station.
     *
     * Time Complexity: O(1)
     */
    Path* getPred() const;

    /**
     * @brief Sets the predecessor path of this station.
     * @param p The predecessor path of this station.
     *
     * Time Complexity: O(1)
     */
    void setPred(Path* p);

    /**
     * @brief Gets the distance to this station.
     * @return The distance to this station.
     *
     * Time Complexity: O(1)
     */
    int getDist() const;

    /**
     * @brief Sets the distance to this station.
     * @param d The distance to this station.
     *
     * Time Complexity: O(1)
     */
    void setDist(int d);

    /**
     * @brief Prints the information of this station.
     *
     * Time Complexity: O(1)
     */
    void print() const;

private:
    int id; /**< The unique identifier of the station */
    string name; /**< The name of the station */
    string district; /**< The district where the station is located */
    string municipality; /**< The municipality where the station is located */
    string township; /**< The township where the station is located */
    string line; /**< The line on which the station is located */
    vector<Path*> paths; /**< The paths connected to this station */
    bool visited; /**< Whether the station has been visited */
    Path* pred; /**< The predecessor path of this station */
    int dist; /**< The distance to this station */
};


#endif //DA_PROJECT1_STATION_H
