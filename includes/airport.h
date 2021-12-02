#ifndef AED2122PROJ_AIRPORT_H
#define AED2122PROJ_AIRPORT_H

#include <iostream>
#include "bst.h"

class LandTransportPlace{
        enum TypeOfTransport{
            SUBWAY,
            TRAIN,
            BUS
        };
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
        std::string name;
        BST<LandTransportPlace> transportPlaces;
    public:
        Airport(std::string name): name(name){}
};



#endif //AED2122PROJ_AIRPORT_H