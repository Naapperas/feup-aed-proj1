//
// Created by naapperas on 01/12/21.
//

#ifndef AED2122PROJ_FLIGHT_H
#define AED2122PROJ_FLIGHT_H

#include <vector>
#include <string>
#include <algorithm>

#include "./passenger.h"
#include "./plane.h"
#include "./airport.h"
#include "./ticket.h"

/**
 * Represents a flight between 2 different destinations.
 */
class Flight {

        static long CURRENT_FLIGHT_NUMBER;
        long flightNumber;

        std::string departureDate;  // format YYYY-MM-DD
        unsigned duration, lotation;

        std::vector<Passenger> passengers;

        Plane plane;
        Airport origin, destiny;

        friend bool operator==(const Flight& a, const Flight& b) {
            return a.flightNumber == b.flightNumber;
        };

        friend ofstream& operator<<(ofstream& out, Flight& f) {
            out << f.getFlightNumber() << ' ' << f.getDepartureDate() << ' ' << f.getDuration() << ' ' << f.getPlane().getPlate() << ' ' << f.getOriginAirport().getName() << ' ' << f.getDestinationAirport().getName() << '\n';
            return out;
        }

    public:
        /**
         * Creates a new flight.
         *
         * @param departureDate the departureDate for this flight in the format "DD-MM-YYYY"
         * @param duration the duration of this flight in seconds
         * @param p the plane responsible for carrying this flight through
         * @param origin the origin airport of this flight
         * @param destiny the destiny airport of this flight
         */
        Flight(const std::string& departureDate,
               unsigned int duration, const Plane& p, const Airport& origin,
               const Airport& destiny) : flightNumber(CURRENT_FLIGHT_NUMBER++), departureDate(departureDate),
               duration(duration), plane(p), origin(origin), destiny(destiny), lotation(0) {}

        /**
         * Creates a new flight.
         *
         * @param flightNumber the identification number of this flight
         * @param departureDate the departureDate for this flight in the format "DD-MM-YYYY"
         * @param duration the duration of this flight in seconds
         * @param p the plane responsible for carrying this flight through
         * @param origin the origin airport of this flight
         * @param destiny the destiny airport of this flight
         */
        Flight(long flightNumber, const std::string& departureDate,
               unsigned int duration, const Plane& p, const Airport& origin,
               const Airport& destiny) : Flight(departureDate, duration, p, origin, destiny) {
            this->flightNumber = flightNumber;
        }

        /**
         * Returns this flight's associated identification number.
         *
         * @return this flight's associated identification number.
         */
        long getFlightNumber() const {
            return flightNumber;
        }

        /**
         * Returns this flight's departure date.
         *
         * @return this flight's departure date
         */
        const std::string& getDepartureDate() const {
            return departureDate;
        }

        /**
         * Returns this flight's duration.
         *
         * @return this flight's duration
         */
        unsigned int getDuration() const {
            return duration;
        }

        /**
         * Returns this flight's current lotation.
         *
         * @return this flight's current lotation
         */
        unsigned getLotation() const {
            return lotation;
        }

        /**
         * Adds a passenger to this flight if there is still space for them.
         *
         * @param ticket the ticket of the passanger wanting to board this flight
         */
        bool addPassenger(const Ticket& ticket);

        /**
         * Adds the list of passengers given as argument, only if there is still enough space left for the entire group.
         *
         * @param tickets the tickets of the group wanting to board the flight
         */
        bool addPassengers(const std::vector<Ticket>& tickets);

        /**
         * Returns the plane associated with this flight.
         *
         * @return the plane associated with this flight
         */
        Plane& getPlane() {
            return this->plane;
        };

        /**
         * Returns the destination airport for this flight.
         *
         * @return the destination airport for this flight
         */
        Airport& getDestinationAirport() {
            return this->destiny;
        };

        /**
         * Returns the origin airport for this flight.
         *
         * @return the origin airport for this flight
         */
        Airport& getOriginAirport() {
            return this->origin;
        };

        void setDepartureDate(const std::string& date){
            this->departureDate=date;
        }

        /**
         * Executes this flight
         * Effectively, this function transfers luggage from the passengers to the airport and then to the plane while boarding said passengers. Then the plane is transfered from the origin airport to the destination airport and cargo is offloaded.
         * @return true if executed successfully else false
         */
        std::pair<Airport, Airport> execute();
};

#endif //AED2122PROJ_FLIGHT_H
