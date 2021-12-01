//
// Created by naapperas on 01/12/21.
//

#ifndef AED2122PROJ_FLIGHT_H
#define AED2122PROJ_FLIGHT_H

class Flight {
        long flightNumber;
        std::string departureDate, destination, origin;
        unsigned duration;
    public:
        Flight(long flightNumber, const std::string &departureDate, const std::string &destination,
           const std::string &origin, unsigned int duration) : flightNumber(flightNumber), departureDate(departureDate),
                                                               destination(destination), origin(origin),
                                                               duration(duration) { }

        long getFlightNumber() const {
            return flightNumber;
        }

        const std::string getDepartureDate() const {
            return departureDate;
        }

        const std::string getDestination() const {
            return destination;
        }

        const std::string &getOrigin() const {
            return origin;
        }

        unsigned int getDuration() const {
            return duration;
        }
};

#endif //AED2122PROJ_FLIGHT_H
