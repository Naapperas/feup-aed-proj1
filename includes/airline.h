//
// Created by naapperas on 13/12/21.
//

#ifndef AED2122PROJ_AIRLINE_H
#define AED2122PROJ_AIRLINE_H

#include <string>

#include "flight.h"
#include "airport.h"

/**
 * The central point of the application, this is supposed to represent the airline for whom the application is being built for
 */
class Airline {

        std::list<FlightPlan> flightPlans;
        std::vector<Plane> ownedPlanes;
        std::vector<Flight> upcomingFlights;

        std::string airlineName;

        static Airline* instance;
    public:
        explicit Airline(const std::string& name);

        bool addPlaneToAirlineFleet(const Plane& plane);

        bool addFlightToPlane(const Plane& plane, const Flight& flight);

        bool addFlightsToPlane(const Plane& plane, const std::list<Flight>& flights);

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
        void listCurrentPlanes() const;

        const std::string& getName() const {
            return this->airlineName;
        }
};


#endif //AED2122PROJ_AIRLINE_H
