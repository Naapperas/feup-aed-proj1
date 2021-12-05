//
// Created by naapperas on 03/12/21.
//

#include "../includes/plane.h"

/**
 * Adds a flight to this plane's flight plan.
 *
 * @param flight a pointer to the new flight to add
 */
void Plane::addFlightToPlan(Flight* flight) {
    this->flightPlan.push_back(flight);
}

bool Plane::getPassengerList(long flightNumber, std::vector<Passenger*>& planePassangers) const {

    auto flight_itr = std::find_if(this->flightPlan.begin(), this->flightPlan.end(), [flightNumber](Flight* flight) { return flight->getFlightNumber() == flightNumber; });

    if (flight_itr == this->flightPlan.end())
        return false;

    planePassangers.clear();

    auto flight = *flight_itr;

    for (auto passenger : flight->getPassengers())
        planePassangers.push_back(passenger);

    return true;
}
