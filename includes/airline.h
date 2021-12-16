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

        bool addPlaneToAirlineFleet(const Plane& plane);

        bool addFlightToPlane(const Plane& plane, const Flight& flight);

        bool addFlightsToPlane(const Plane& plane, const std::list<Flight>& flights);

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

        void listCurrentFlights() const;
        void listCurrentPlanes(bool verbose = true) const;
        void purchasePlane();
        void registerTransportPlace();

        const std::string& getName() const {
            return this->airlineName;
        }
};


#endif //AED2122PROJ_AIRLINE_H
