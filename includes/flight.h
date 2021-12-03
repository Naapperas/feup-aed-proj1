//
// Created by naapperas on 01/12/21.
//

#ifndef AED2122PROJ_FLIGHT_H
#define AED2122PROJ_FLIGHT_H

// #include "./plane.h"
#include "./passenger.h"

class Plane;
class Flight;

class Ticket {
    bool hasLuggage;
    Flight* flight;
    Passenger* passenger;
public:
    Ticket(bool hasLuggage, Flight* flight, Passenger* passenger) : hasLuggage(hasLuggage), flight(flight), passenger(passenger) {}

    virtual ~Ticket() {
        delete passenger;
    }

    bool isHasLuggage() const {
        return hasLuggage;
    }

    Flight* getFlight() const {
        return flight;
    }

    Passenger* getPassenger() const {
        return passenger;
    }

};

class Flight {
        long flightNumber;
        std::string departureDate, destination, origin;
        unsigned duration;
        Plane* plane;
        std::vector<Ticket*> passengers;
    public:
        Flight(long flightNumber, const std::string &departureDate, const std::string &destination,
           const std::string &origin, unsigned int duration, Plane* plane) : flightNumber(flightNumber), departureDate(departureDate),
                                                               destination(destination), origin(origin),
                                                               duration(duration), plane(plane) { }

        virtual ~Flight() {
            // since a plane belongs to many flights, it should be the plane deleting flights;
            for (auto ticket : passengers)
                if (ticket != nullptr)
                    delete ticket;
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

        const std::string getOrigin() const {
            return origin;
        }

        unsigned int getDuration() const {
            return duration;
        }

        Plane* getPlane() const {
            return plane;
        }

        void addPassenger(Passenger* passenger, bool hasLuggage) {
            if (plane->getLotation() < plane->getCapacity()) {
                this->passengers.push_back(new Ticket(hasLuggage, this, passenger));
                plane->increaseLotation();
            }
        }

        std::vector<Passenger*> getPassengers() const {
            std::vector<Passenger*> ret;

            for (auto ticket : passengers)
                ret.push_back(ticket->getPassenger());

            return ret;
        }
};

#endif //AED2122PROJ_FLIGHT_H
