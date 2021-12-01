#ifndef AED2122PROJ_AIRPORT_H
#define AED2122PROJ_AIRPORT_H

#include <iostream>

class LandTransportPlace{
        enum TypeOfTransport{
            METRO,
            COMBOIO,
            AUTOCARRO
        };
        TypeOfTransport type;
        unsigned distance, openTime, closeTime; // the last two shouldn't be unsigned, need to assign them to another type later
        friend bool operator <(const LandTransportPlace & a, const LandTransportPlace & b);
        friend ostream& operator <<(ostream& out ,const LandTransportPlace & a);
    public:
        LandTransportPlace(TypeOfTransport type, unsigned distance, unsigned openTime, unsigned closeTime): type(type),
            distance(distance), openTime(openTime), closeTime(closeTime){}
};

bool operator<(const LandTransportPlace &a, const LandTransportPlace &b) {
    return (a.distance < b.distance);
}

ostream& operator <<(ostream& out , const LandTransportPlace &a) {
    out << a.type << ' ' << a.distance << "m " << "Open from: " << a.openTime << ' to ' << a.closeTime << endl;
    return out;
}


class Airport{
        string cityName;
        // binary search tree of LandTransportPlace (include bst.h?)
};



#endif //AED2122PROJ_AIRPORT_H