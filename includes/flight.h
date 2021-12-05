//
// Created by naapperas on 01/12/21.
//

#ifndef AED2122PROJ_FLIGHT_H
#define AED2122PROJ_FLIGHT_H

#include <vector>
#include <string>
#include <algorithm>

class Plane;

class Flight {

        static int CURRENT_FLIGHT_ID;
        int id;
        static std::vector<Flight*> items;

        long flightNumber;
        std::string departureDate, destination, origin;
        unsigned duration;
        int planeId;
    public:
        Flight(long flightNumber, const std::string &departureDate, const std::string &destination,
           const std::string &origin, unsigned int duration, int planeId) : id(CURRENT_FLIGHT_ID++), flightNumber(flightNumber), departureDate(departureDate),
                                                               destination(destination), origin(origin),
                                                               duration(duration), planeId(planeId) {
            items.push_back(this);
        }

        long getFlightNumber() const {
            return flightNumber;
        }

        const std::string& getDepartureDate() const {
            return departureDate;
        }

        const std::string& getDestination() const {
            return destination;
        }

        const std::string& getOrigin() const {
            return origin;
        }

        unsigned int getDuration() const {
            return duration;
        }

        int getId() const {
            return this->id;
        }

        const Plane& getPlane() const;

        static const Flight& getFlight(int f);
};

#endif //AED2122PROJ_FLIGHT_H
