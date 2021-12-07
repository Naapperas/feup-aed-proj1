#ifndef AED2122PROJ_AIRPORT_H
#define AED2122PROJ_AIRPORT_H

#include <fstream>
#include <sstream>
#include <vector>
#include "bst.h"

class LandTransportPlace {
    public:
        enum TypeOfTransport{
            SUBWAY,
            TRAIN,
            BUS
        };
    private:
        static const std::vector<std::string> typePrint;
        TypeOfTransport type;
        unsigned int distance;
        std::string openTime, closeTime;

        friend bool operator <(const LandTransportPlace & a, const LandTransportPlace & b);
        friend ostream& operator <<(ostream& out ,const LandTransportPlace & a);
    public:
        LandTransportPlace(TypeOfTransport type, unsigned distance, std::string openTime, std::string closeTime): type(type), distance(distance), openTime(openTime), closeTime(closeTime) {}

        TypeOfTransport getType() const{
            return type;
        }

        unsigned int getDistance() const{
            return distance;
        }

        std::string getOpenTime() const{
            return openTime;
        }

        std::string getCloseTime() const{
            return closeTime;
        }
};

bool operator<(const LandTransportPlace &a, const LandTransportPlace &b) {
    return (a.distance < b.distance);
}

ostream& operator <<(ostream& out , const LandTransportPlace &a) {
    out << a.typePrint.at(a.type) << ' ' << a.distance << "m " << "Open from: " << a.openTime << " to " << a.closeTime << endl;
    return out;
}


class Airport {

        static int CURRENT_AIRPORT_ID;
        int id;
        static std::vector<Airport*> items;

        std::string name;
        BST<LandTransportPlace> transportPlaces;

        void readFile(const std::ifstream &f);
        void writeToFile();
        void readInput(unsigned n);
    public:
        Airport(std::string name); // when there is no file to read from (create airport from scratch)
        Airport(std::string name, const std::ifstream &f); // when there is a file (existing airport)
        void printTransportPlaces();

        static const Airport& getAirport();
};

#endif //AED2122PROJ_AIRPORT_H