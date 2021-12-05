//
// Created by naapperas on 05/12/21.
//

#include "../includes/flight.h"

int Flight::CURRENT_FLIGHT_ID = 1;

const Flight& Flight::getFlight(int flightId) {
    auto flight = std::find_if(Flight::items.begin(), Flight::items.end(), [flightId](Flight* l) { return l->id == flightId; });

    if (flight != Flight::items.end())
        return *(*flight);

    throw "No flight with given id";
}