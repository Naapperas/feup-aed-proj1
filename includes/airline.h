//
// Created by naapperas on 13/12/21.
//

#ifndef AED2122PROJ_AIRLINE_H
#define AED2122PROJ_AIRLINE_H

#include <string>
#include <algorithm>

#include "flight.h"
#include "airport.h"

/**
 * The central point of the application, this is supposed to represent the airline for whom the application is being built for.
 */
class Airline {

        std::list<FlightPlan> flightPlans;
        std::vector<Plane> ownedPlanes;
        std::vector<Flight> upcomingFlights;
        std::vector<Airport> airports;

        std::string airlineName;

        static Airline* instance;

        void storePlanes() const;
        void storeCleaningServices(const Plane& plane) const;
        void storeAirports() const;
        void storeTransportPlaces(const Airport& airport) const;
        void listAirports() const;
    public:
        explicit Airline(const std::string& name);
        ~Airline() {
            this->storePlanes();
            this->storeAirports();
        }

        /**
         * Add a new plane to the currently owned planes
         * @param plane plane to be added
         * @return true if added successfully (this plane wasn't owned already) else false
         */
        bool addPlaneToAirlineFleet(const Plane& plane);

        /**
         * Add a flight to a plane's flight plan
         * @param plane plane that will perform this flight
         * @param flight flight to be added
         * @return
         */
        bool addFlightToPlane(const Plane& plane, const Flight& flight);

        /**
         * Add a list of flights to a plane's flight plan
         * @param plane plane that will perform these flights
         * @param flight list of flights to be added
         * @return
         */
        bool addFlightsToPlane(const Plane& plane, const std::list<Flight>& flights);

        /**
         * Cancel a flight (essentially deleting it)
         * @param flightNumber identification number of the flight to be canceled
         * @return true if cancelled successfully (flightNumber corresponded to an existing flight) else false
         */
        bool cancelFlight(long flightNumber);

        static void setInstance(Airline* instance) {
            if (Airline::instance == NULL)
                Airline::instance = instance;
        }

        static Airline& getInstance() {

            if (Airline::instance == NULL)
                throw std::string("Error");

            return *Airline::instance;
        }

        /**
         * Print all scheduled flights
         */
        void listCurrentFlights() const;

        /**
         * Print all owned planes
         * @param verbose if set to false only displays essential information (plate and type)
         */
        void listCurrentPlanes(bool verbose = true) const;

        /**
         * Add a new plane to the owned planes
         */
        void purchasePlane();
        void registerTransportPlace();

        const std::string& getName() const {
            return this->airlineName;
        }
};


#endif //AED2122PROJ_AIRLINE_H
