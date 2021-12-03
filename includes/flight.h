//
// Created by naapperas on 01/12/21.
//

#ifndef AED2122PROJ_FLIGHT_H
#define AED2122PROJ_FLIGHT_H

// #include "./plane.h"

class Plane;

class Flight {
        long flightNumber;
        std::string departureDate, destination, origin;
        unsigned duration;
        Plane* plane;
    public:
        Flight(long flightNumber, const std::string &departureDate, const std::string &destination,
           const std::string &origin, unsigned int duration, Plane* plane) : flightNumber(flightNumber), departureDate(departureDate),
                                                               destination(destination), origin(origin),
                                                               duration(duration), plane(plane) { }

        virtual ~Flight() {
            std::cout << "FLight destructor" << std::endl;
            if (plane != nullptr) {
                std::cout << "Deleting Flight reference to Plane" << std::endl;
                delete plane;
            }
        }

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

        Plane* getPlane() const {
            return plane;
        }
};

class Ticket {
        bool hasLuggage;
        Flight* flight;
    public:
        Ticket(bool hasLuggage, Flight *flight) : hasLuggage(hasLuggage), flight(flight) {}

        virtual ~Ticket() {
            std::cout << "Ticket destructor" << std::endl;
            if (flight != nullptr) {
                std::cout << "Deleting Tickets reference to FLight" << std::endl;
                delete flight;
            }
        }

        bool isHasLuggage() const {
            return hasLuggage;
        }

        Flight *getFlight() const {
            return flight;
        }
};

#endif //AED2122PROJ_FLIGHT_H
