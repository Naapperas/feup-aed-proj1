#ifndef AED2122PROJ_AIRPORT_H
#define AED2122PROJ_AIRPORT_H

#include <vector>
#include <list>

#include "bst.h"
#include "plane.h"
#include "ticket.h"
#include "passenger.h"
#include "luggageTransport.h"
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

        /**
         * Returns the plane associated with this flightPlan.
         *
         * @return the plane associated with this flightPlan
         */
        const Plane& getPlane() const {
            return this->plane;
        }

        bool removeFlight(long flightNumber);

};

/**
 * Represents a land transport (subway, train, bus) near an airport
 * An object of LandTransportPlace is relative to only one Airport (if there are two airports close to each other, and both are close to a local train station,
 * each one keeps their own LandTransportPlace for that train station, mainly because of the different distances to each airport)
 */
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

        /**
         * Creates a new LandTransportPlace
         * @param type Type of transport (SUBWAY, TRAIN or BUS)
         * @param distance Distance from the nearby airport
         * @param openTime Time of first departure (first train leaving at 6:00 for example)
         * @param closeTime Time of last departure (last bus leaving at 23:00 for example)
         */
        LandTransportPlace(TypeOfTransport type, unsigned distance, const std::string& openTime, const std::string& closeTime): type(type), distance(distance), openTime(openTime), closeTime(closeTime) {}

        /**
         * Return this place's transport type (SUBWAY, TRAIN or BUS)
         * @return this place's transport type (SUBWAY, TRAIN or BUS)
         */
        TypeOfTransport getType() const{
            return type;
        }

        /**
         * Return this place's transport type as a string (the corresponding strings to each type are stored in typePrint)
         * @return this place's transport type as a string
         */
        std::string getTypeString() const{
            return typePrint.at(type);
        }

        /**
         * Return this place's distance to it's nearby airport
         * @return this place's distance to it's nearby airport
         */
        unsigned int getDistance() const{
            return distance;
        }

        /**
         * Return this place's open time (time of first departure)
         * @return this place's open time (time of first departure)
         */
        std::string getOpenTime() const{
            return openTime;
        }

        /**
         * Return this place's close time (time of last departure)
         * @return this place's close time (time of last departure)
         */
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

        std::queue<Luggage> luggageTransportBelt;
        LuggageTransport transport{4, 5};

        /**
         * Get information on this airport's land transport places from a text file to transportPlaces
         * @param f file containing information on this airport's land transport places
         */
        void readFile(std::ifstream &f);

        /**
         * Store the information on transportPlaces in a text file <name>.txt
         */
        void writeToFile();

        /**
         * Get information on this airport's land transport places from user input to transportPlaces
         * @param n number of land transport places
         */
        void readInput(unsigned n);

        /**
         * Carry luggage from the conveyor belt to the luggageTransport
         */
        void loadLuggageToTransport();
    public:

        /**
         * Creates a new airport
         * @param name Name of the airport
         */
        Airport(std::string name);

        /**
         * Print the information in transportPlaces to the console
         */
        void printTransportPlaces() const;

        Ticket purchaseTicket(Flight& flight, const Passenger& passenger);

        /**
         * Emplaces some luggage on this airport's transport belt to be carried to a plane by the Luggage Transportation Service
         *
         * @param l the luggage to transport
         */
        void addLuggageToTransportBelt(const Luggage& l);

        /**
         *  Lands a plane at this airport
         *
         * @param plane the plane to land
         */
        void landPlane(const Plane& plane);

        /**
         * Makes a plane take off from this location
         *
         * @param plane the plane taking off
         */
        void planeDeparture(const Plane& plane);

        /**
         * Checks if a plane is currently landed in this airport
         * @param plane
         * @return true if the plane is landed else false
         */
        bool planeIsLanded(const Plane& plane);

        /**
         * Loads the cargo to the given plane.
         *
         * @param plane the plane that should have cargo loaded
         */
        void loadCargo(Plane& plane);

        /**
         * Offloads this plane's cargo to be delivered at this airport
         *
         * @param plane the plane whose cargo should be offloaded
         */
        void offloadCargo(Plane& plane);
};

#endif //AED2122PROJ_AIRPORT_H