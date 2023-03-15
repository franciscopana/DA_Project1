#include "Station.h"

Station::Station(int id, string name, string district, string municipality, string township, string line) {
    this->id = id;
    this->name = name;
    this->district = district;
    this->municipality = municipality;
    this->township = township;
    this->line = line;
    this->paths = vector<Path*>();
    this->visited = false;
}

string Station::getName() const {
    return name;
}

string Station::getDistrict() const {
    return district;
}

string Station::getMunicipality() const {
    return municipality;
}

string Station::getTownship() const {
    return township;
}

string Station::getLine() const {
    return line;
}

int Station::getId() const {
    return id;
}

vector<Path*> Station::getPaths() const {
    return paths;
}

void Station::addPath(Path* path) {
    paths.push_back(path);
}

bool Station::isVisited() const {
    return visited;
}

void Station::setVisited(bool v) {
    this->visited = v;
}