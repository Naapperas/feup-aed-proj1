#ifndef AED2122PROJ_AIRPORT_H
#define AED2122PROJ_AIRPORT_H

#include <vector>
#include <list>
#include <fstream>
#include <ctime>

#include "bst.h"
#include "plane.h"
#include "ticket.h"
#include "passenger.h"
#include "luggageTransport.h"

class Flight;

class FlightPlan {
        Plane* plane;
        std::list<Flight*> plan;

        /**
         * Compares the given flight departure date against the current time
         *
         * @param flightDepartureDate the departure date
         * @return true if the given date is prior to the current date
         */
        bool isPast(std::string flightDepartureDate) {

            time_t now = time(0);
            tm *currentDateTime = gmtime(&now);

            int day, month, year;
            char delim;

            stringstream ss{flightDepartureDate};
            ss >> year >> delim >> month >> delim >> day;

            if (year == (1900 + currentDateTime->tm_year))
                if (month == (currentDateTime->tm_mon+1))
                    return day < currentDateTime->tm_mday;
                else
                    return month < (currentDateTime->tm_mon+1);
            else
                return year < (1900 + currentDateTime->tm_year);
        }

    public:
        FlightPlan(Plane* p) : plane(p) {}

        /**
         * Adds a flight to this plane's flightPlan if it is not already present.
         *
         * @param f the flight to add
         * @return false if the flight already existed in the planes flightPlan, true otherwise
         */
        bool addFlightToPlan(Flight* f);

        /**
         * Performs flights with a departure date prior to the current date
         */
        void performFlights();

        /**
         * Returns the plane associated with this flightPlan.
         *
         * @return the plane associated with this flightPlan
         */
        Plane* getPlane() const {
            return this->plane;
        }

        /**
         * Removes a flight from this FlightPlan's list of flights
         * @param flightNumber identification number of the flight to be removed
         * @return true if flight is removed successfully else false
         */
        bool removeFlight(long flightNumber);

        /**
         * Updates the departure date for a flight from this FlightPlan's list of flights
         * @param flightNumber identification number of the flight to be updated
         * @param newDate new departure date for this flight
         * @return true if flight is updated successfully else false
         */
        bool updateFlight(long flightNumber, std::string newDate);

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

        static TypeOfTransport getTypeOfTransport(unsigned i) {
            switch (i) {
                case 0:
                    return SUBWAY;
                case 1:
                    return TRAIN;
                case 2:
                    return BUS;
            }
        }
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

        std::list<Plane*> landedPlanes; // list for insertion/removal

        std::queue<Luggage*> luggageTransportBelt;
        LuggageTransport transport{4, 5};

        BST<LandTransportPlace> transportPlaces;

        /**
         * Carry luggage from the conveyor belt to the luggageTransport
         */
        void loadLuggageToTransport();

        friend ostream& operator<<(ostream& out, const Airport& a) {
            out << a.name;

            for (const auto& plane : a.landedPlanes)
                out << ' ' << plane->getPlate();
            return out << '\n';
        }

        friend bool operator==(const Airport& a, const Airport& b) {
            return a.getName() == b.getName();
        }


public:

        /**
         * Creates a new airport
         * @param name Name of the airport
         */
        Airport(std::string name) : name(name), transportPlaces(LandTransportPlace(LandTransportPlace::SUBWAY, 0, "", "")) {};

        /**
         * Print the information in transportPlaces to the console
         */
        void printTransportPlaces() const;

        const std::string& getName() const {
            return this->name;
        }

        /**
         * Emplaces some luggage on this airport's transport belt to be carried to a plane by the Luggage Transportation Service
         *
         * @param l the luggage to transport
         */
        void addLuggageToTransportBelt(Luggage* l);

        /**
         *  Lands a plane at this airport
         *
         * @param plane the plane to land
         */
        void landPlane(Plane* plane);

        /**
         * Makes a plane take off from this location
         *
         * @param plane the plane taking off
         */
        void planeDeparture(Plane* plane);

        /**
         * Checks if a plane is currently landed in this airport
         * @param plane
         * @return true if the plane is landed else false
         */
        bool planeIsLanded(Plane* plane);

        /**
         * Loads the cargo to the given plane.
         *
         * @param plane the plane that should have cargo loaded
         */
        void loadCargo(Plane* plane);

        /**
         * Offloads this plane's cargo to be delivered at this airport
         *
         * @param plane the plane whose cargo should be offloaded
         */
        void offloadCargo(Plane* plane);

        /**
         * Store this airport's land transport places info in the dedicated file
         * @param file file that contains information on every airport's land transport places
         */
        void storeTransportPlaces(ofstream& file) const;

        /**
         * Add a new land transport place to transportPlaces
         * @param ltp land transport place to be added/registered
         */
        void registerTransportPlace(const LandTransportPlace& ltp);
};

#endif //AED2122PROJ_AIRPORT_H