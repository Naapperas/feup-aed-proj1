//
// Created by naapperas on 05/12/21.
//

#include "../includes/flight.h"
#include "../includes/plane.h"
#include "../includes/airport.h"

int Flight::CURRENT_FLIGHT_ID = 1;
std::vector<Flight*> Flight::items = std::vector<Flight*>();

const Flight& Flight::getFlight(int flightId) {
    auto flight = std::find_if(Flight::items.begin(), Flight::items.end(), [flightId](Flight* f) { return f->id == flightId; });

    if (flight != Flight::items.end())
        return *(*flight);

    throw "No flight with given id";
}

const Plane& Flight::getPlane() const {
    try {
        return Plane::getPlane(this->planeId);
    } catch (char* err) {
        // no luggage found for the given user, what happened?
        // should never enter this block, add just for safety

        throw "Passanger with no luggage found";
    }
}

const Airport& Flight::getDestinationAirport() const {
    try {
        return Airport::getAirport(this->destinationAirportId);
    } catch (char* err) {
        // no luggage found for the given user, what happened?
        // should never enter this block, add just for safety

        throw "No destination airport found";
    }
}

const Airport& Flight::getOriginAirport() const {
    try {
        return Airport::getAirport(this->originAirportId);
    } catch (char* err) {
        // no luggage found for the given user, what happened?
        // should never enter this block, add just for safety

        throw "No origin airport found";
    }
}