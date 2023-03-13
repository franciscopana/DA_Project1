#ifndef DA_PROJECT1_STATION_H
#define DA_PROJECT1_STATION_H

#include <string>

using namespace std;

class Station {
public:
    Station(string name, string district, string municipality, string township, string line);
    string getName() const;
    string getDistrict() const;
    string getMunicipality() const;
    string getTownship() const;
    string getLine() const;

private:
    string name;
    string district;
    string municipality;
    string township;
    string line;
};


#endif //DA_PROJECT1_STATION_H
