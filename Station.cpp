/**
 * @file Station.cpp
 * @brief Station class implementation
 */

#include "Station.h"

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
Station::Station(int id, string& name, string& district, string& municipality, string& township, string& line) {
    this->id = id;
    this->name = name;
    this->district = district;
    this->municipality = municipality;
    this->township = township;
    this->line = line;
    this->paths = vector<Path*>();
    this->visited = false;
    this->pred = nullptr;
    this->dist = INT_MAX;
}

/**
 * @brief Gets the name of the station.
 * @return The name of the station.
 *
 * Time Complexity: O(1)
 */
string Station::getName() const {
    return name;
}

/**
 * @brief Gets the district where the station is located.
 * @return The district where the station is located.
 *
 * Time Complexity: O(1)
 */

string Station::getDistrict() const {
    return district;
}

/**
 * @brief Gets the municipality where the station is located.
 * @return The municipality where the station is located.
 *
 * Time Complexity: O(1)
 */
string Station::getMunicipality() const {
    return municipality;
}

/**
 * @brief Gets the township where the station is located.
 * @return The township where the station is located.
 *
 * Time Complexity: O(1)
 */
string Station::getTownship() const {
    return township;
}

/**
 * @brief Gets the line on which the station is located.
 * @return The line on which the station is located.
 *
 * Time Complexity: O(1)
 */
string Station::getLine() const {
    return line;
}

/**
 * @brief Gets the ID of the station.
 * @return The ID of the station.
 *
 * Time Complexity: O(1)
 */
int Station::getId() const {
    return id;
}

/**
 * @brief Gets the paths connected to this station.
 * @return The paths connected to this station.
 *
 * Time Complexity: O(1)
 */
vector<Path*> Station::getPaths() const {
    return paths;
}

/**
 * @brief Adds a path to the station.
 * @param path The path to be added.
 *
 * Time Complexity: O(1)
 */
void Station::addPath(Path* path) {
    paths.push_back(path);
}

<<<<<<< HEAD
void Station::removePath() {
    paths.pop_back();
}

=======
/**
 * @brief Gets the visited status of the station.
 * @return The visited status of the station.
 *
 * Time Complexity: O(1)
 */
>>>>>>> doxygen
bool Station::isVisited() const {
    return visited;
}

/**
 * @brief Sets the visited status of the station.
 * @param v The visited status of the station.
 *
 * Time Complexity: O(1)
 */
void Station::setVisited(bool v) {
    this->visited = v;
}

/**
 * @brief Gets the predecessor of the station.
 * @return The predecessor of the station.
 *
 * Time Complexity: O(1)
 */
Path* Station::getPred() const {
    return pred;
}

/**
 * @brief Sets the predecessor of the station.
 * @param p The new predecessor of the station.
 *
 * Time Complexity: O(1)
 */
void Station::setPred(Path* p) {
    this->pred = p;
}

/**
 * @brief Gets the distance of the station.
 * @return The distance of the station.
 *
 * Time Complexity: O(1)
 */
int Station::getDist() const {
    return dist;
}

/**
 * @brief Sets the distance of the station.
 * @param d The new distance of the station.
 *
 * Time Complexity: O(1)
 */
void Station::setDist(int d) {
    this->dist = d;
}

/**
 * @brief Prints the station.
 *
 * Time Complexity: O(1)
 */
void Station::print() const{
    cout << "ID: " << id << " | " << name << " | " << district << " | " << municipality << " | " << township << " | " << line << endl;
}