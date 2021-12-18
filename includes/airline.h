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

        std::list<FlightPlan*> flightPlans;
        std::vector<Plane*> ownedPlanes;
        std::vector<Flight*> upcomingFlights;
        std::vector<Airport*> airports;

        std::string airlineName;

        static Airline* instance;

        void storePlanes() const;
        void storeCleaningServices(Plane* plane) const;
        void storeAirports() const;
        void storeTransportPlaces(Airport* airport) const;
        void listAirports() const;
        void storeFlights() const;

        std::vector<Flight*> getValidFlights() const;

    public:
        explicit Airline(const std::string& name);
        ~Airline() {
            this->storePlanes();
            this->storeAirports();
            this->storeFlights();

            for (auto plane : this->ownedPlanes)
                delete plane;

            for (auto flight : this->upcomingFlights)
                delete flight;

            for (auto plan : this->flightPlans)
                delete plan;

            for (auto airport : this->airports)
                delete airport;

        }

        /**
         * Add a new plane to the currently owned planes
         * @param plane plane to be added
         * @return true if added successfully (this plane wasn't owned already) else false
         */
        bool addPlaneToAirlineFleet(Plane* plane);

        /**
         * Add a flight to a plane's flight plan
         * @param plane plane that will perform this flight
         * @param flight flight to be added
         * @return
         */
        bool addFlightToPlane(Plane* plane, Flight* flight);

        /**
         * Add a list of flights to a plane's flight plan
         * @param plane plane that will perform these flights
         * @param flight list of flights to be added
         * @return
         */
        bool addFlightsToPlane(Plane* plane, const std::list<Flight*>& flights);

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

        /**
         * Add a new airport as a possible origin/destination for this company´s flights'
         * @param airport airport to be added
         * @return true if added successfully (this airport didn't exist before) else false
         */
        bool addAirport(Airport* airport);

        /**
         * Register a new airport
         */
        void registerAirport();

        /**
         * Register a new transport place
         */
        void registerTransportPlace();

        /**
         * Cancel a flight (essentially deleting it)
         * @return true if cancelled successfully (deleted an existing flight) else false
         */
        bool cancelFlight();

        /**
         * Reschedule a flight, updating it's departure date
         * @return true if rescheduled successfully (updated an existing flight) else false
         */
        bool rescheduleFlight();

        /**
         *
         */
        void createFlight();

        /**
         *
         */
        void purchaseTicket();

        /**
         *
         */
        void listTransportPlaces() const;

        /**
         *
         * @return
         */
        const std::string& getName() const {
            return this->airlineName;
        }


        /**
         *
         */
        void addCleaningService();


};


#endif //AED2122PROJ_AIRLINE_H
