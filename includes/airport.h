#ifndef AED2122PROJ_AIRPORT_H
#define AED2122PROJ_AIRPORT_H

#include <vector>
#include <list>

#include "bst.h"
#include "plane.h"
#include "ticket.h"
#include "passenger.h"
//#include "flight.h"
class Flight;

class FlightPlan {
        Plane plane;
        std::list<Flight> plan;
    public:
        FlightPlan(const Plane& p) : plane(p) {}

        /**
         * Adds a flight to this plane's flightPlan if it is not already present.
         *
         * @param f the flight to add
         * @return false if the flight already existed in the planes flightPlan, true otherwise
         */
        bool addFlightToPlan(const Flight& f);

        /**
         * Performs the first flight in the flightPlan
         */
        void performFlight() {
            this->plan.pop_front();
        }

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
        LandTransportPlace(TypeOfTransport type, unsigned distance, const std::string& openTime, const std::string& closeTime): type(type), distance(distance), openTime(openTime), closeTime(closeTime) {}

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
        std::list<Plane> landedPlanes; // list for insertion/removal
        std::vector<FlightPlan> flightPlans;

        void readFile(std::ifstream &f);
        void writeToFile();
        void readInput(unsigned n);
    public:
        Airport(std::string name);

        void printTransportPlaces() const;

        Ticket purchaseTicket(Flight& flight, const Passenger& passenger);

        void landPlane(const Plane& plane);
        void planeDeparture(const Plane& plane);

};

#endif //AED2122PROJ_AIRPORT_H