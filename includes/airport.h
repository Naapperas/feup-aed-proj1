#ifndef AED2122PROJ_AIRPORT_H
#define AED2122PROJ_AIRPORT_H

#include <fstream>
#include <sstream>
#include <vector>

#include "bst.h"
#include "plane.h"
#include "ticket.h"
#include "passenger.h"
//#include "flight.h"
class Flight;

class FLightPlan {

};

class LandTransportPlace {
    public:
        enum TypeOfTransport{
            SUBWAY,
            TRAIN,
            BUS
        };
        static const std::vector<std::string> typePrint;
    private:

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

        std::string getTypeString() const{
            return typePrint.at(type);
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

/**
 * Represents an Airport where planes can land and passengers can buy tickets for flights
 */
class Airport {
        std::string name;

        BST<LandTransportPlace> transportPlaces;
        std::vector<Plane> landedPlanes; // needs to allow random removal, vector > list for insertion/removal

        void readFile(std::ifstream &f);
        void writeToFile();
        void readInput(unsigned n);
    public:
        Airport(std::string name); // when there is no file to read from (create airport from scratch)
        Airport(std::string name, std::ifstream &f); // when there is a file (existing airport)

        void printTransportPlaces() const;

        Ticket purchaseTicket(Flight& flight, const Passenger& passenger);

        void landPlane(const Plane& plane);
        void planeDeparture(const Plane& plane);

};

#endif //AED2122PROJ_AIRPORT_H