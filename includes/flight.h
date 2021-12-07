//
// Created by naapperas on 01/12/21.
//

#ifndef AED2122PROJ_FLIGHT_H
#define AED2122PROJ_FLIGHT_H

#include <vector>
#include <string>
#include <algorithm>

#include "./passenger.h"

class Plane;
class Airport;

class Flight {

        static int CURRENT_FLIGHT_ID;
        int id;
        static std::vector<Flight*> items;

        long flightNumber;
        std::string departureDate;
        unsigned duration, lotation;
        std::vector<int> passengers;
        int planeId, destinationAirportId, originAirportId;
    public:
        Flight(long flightNumber, const std::string &departureDate, const std::string &destination,
           const std::string &origin, unsigned int duration, int planeId) : id(CURRENT_FLIGHT_ID++), flightNumber(flightNumber), departureDate(departureDate),
                                                               duration(duration), planeId(planeId), lotation(0) {
            items.push_back(this);
        }

        long getFlightNumber() const {
            return flightNumber;
        }

        const std::string& getDepartureDate() const {
            return departureDate;
        }

        unsigned int getDuration() const {
            return duration;
        }

        unsigned getLotation() const {
            return lotation;
        }

        [[nodiscard]]
        int getId() const {
            return this->id;
        }

        void addTicket(const Passenger& passenger) { this->addTicket(passenger.getId()); };
        void addTicket(int passengerId);

        const Plane& getPlane() const;

        const Airport& getDestinationAirport() const;

        const Airport& getOriginAirport() const;

        static const Flight& getFlight(int f);
};

#endif //AED2122PROJ_FLIGHT_H
