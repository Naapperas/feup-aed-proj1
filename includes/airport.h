#ifndef AED2122PROJ_AIRPORT_H
#define AED2122PROJ_AIRPORT_H

#include <fstream>
#include <sstream>
#include "bst.h"

class LandTransportPlace{
    public:
        enum TypeOfTransport{
            SUBWAY,
            TRAIN,
            BUS
        };
    private:
        TypeOfTransport type;
        unsigned int distance;
        std::string openTime, closeTime;

        friend bool operator <(const LandTransportPlace & a, const LandTransportPlace & b);
        friend ostream& operator <<(ostream& out ,const LandTransportPlace & a);
    public:
        LandTransportPlace(TypeOfTransport type, unsigned distance, std::string openTime, std::string closeTime): type(type), distance(distance), openTime(openTime), closeTime(closeTime){}
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
    out << a.type << ' ' << a.distance << "m " << "Open from: " << a.openTime << ' to ' << a.closeTime << endl;
    return out;
}


class Airport{
    private:
        std::string name;
        BST<LandTransportPlace> transportPlaces;

        void readFile(ifstream &f);
    public:
        Airport(std::string name);
};



#endif //AED2122PROJ_AIRPORT_H