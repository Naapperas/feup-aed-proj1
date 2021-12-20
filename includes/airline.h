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

        /**
         * Store the plane's information on the dedicated text file
         */
        void storePlanes() const;

        /**
         * Store the cleaning service's information on the dedicated text file
         */
        void storeCleaningServices(Plane* plane) const;

        /**
         * Store the airport's information on the dedicated text file
         */
        void storeAirports() const;

        /**
         * Store the land transport place's information from an airport on the dedicated text file
         * @param airport
         */
        void storeTransportPlaces(Airport* airport) const;

        /**
         * Store the flight's information on the dedicated text file
         */
        void storeFlights() const;

        /**
         * List airports on screen
         */
        void listAirports() const;

        /**
         * Stores the passengers currently registered to take a flight.
         *
         * @param flight the flight to serialize
         */
        void storePassengers(Flight* flight) const;

        /**
         * Returns a filtered view of all the flights made by this airline: the applied filter removes the flights that have already been done
         *
         * @return the flights that will occur in the future.
         */
        [[nodiscard]] std::vector<Flight*> getValidFlights() const;

    public:
        /**
         * Creates the Airline object with the given name.
         *
         * @param name the name of this airline
         */
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
         * Add a new plane to the currently owned planes.
         *
         * @param plane plane to be added
         * @return true if added successfully (this plane wasn't owned already) else false
         */
        bool addPlaneToAirlineFleet(Plane* plane);

        /**
         * Add a flight to a plane's flight plan.
         *
         * @param plane plane that will perform this flight
         * @param flight flight to be added
         * @return weather the plane already existed in the airline fleet or not
         */
        bool addFlightToPlane(Plane* plane, Flight* flight);

        /**
         * Add a list of flights to a plane's flight plan.
         *
         * @param plane plane that will perform these flights
         * @param flights list of flights to be added
         * @return weather the plane alreay existed in the fleet or not
         */
        bool addFlightsToPlane(Plane* plane, const std::list<Flight*>& flights);

        /**
         * Since there is olny one airline per application, this method serves as the entrypoint for the singleton pattern.
         *
         * @param instance the airline instance that is going to be global throughout the application
         */
        static void setInstance(Airline* instance) {
            if (Airline::instance == NULL)
                Airline::instance = instance;
        }

        /**
         * Returns the Airline singleton.
         *
         * @return the global airline instance
         */
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
         * Schedule a new flight
         */
        void createFlight();

        /**
         * Purchase tickets for one or more passengers
         */
        void purchaseTicket();

        /**
         * Used by clients to list the transport places near any airport
         */
        void listTransportPlaces() const;

        /**
         *
         * @return the name of this airline
         */
        const std::string& getName() const {
            return this->airlineName;
        }


        /**
         * Register a new cleaning service for any plane
         */
        void addCleaningService();


};


#endif //AED2122PROJ_AIRLINE_H
