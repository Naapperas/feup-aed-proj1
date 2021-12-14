//
// Created by naapperas on 05/12/21.
//

#include "../includes/flight.h"

long Flight::CURRENT_FLIGHT_NUMBER = 1;

bool Flight::addPassenger(const Ticket& ticket) {
    if (this->lotation < this->getPlane().getCapacity()) {
        this->passengers.emplace_back(ticket.getPassenger());
        this->lotation++;
        return true;
    }
    return false;
}

bool Flight::addPassengers(const std::vector<Ticket>& tickets) {
    if (this->lotation + tickets.size() < this->getPlane().getCapacity()) {
        for (auto ticket : tickets)
            this->addPassenger(ticket);
        return true;
    }
    return false;
}

void Flight::execute() {

    auto &origin = this->getOriginAirport(), &destination = this->getDestinationAirport();
    auto &plane = this->getPlane();

    for (auto& passenger : this->passengers)
        origin.addLuggageToTransportBelt(passenger.getLuggage());

    origin.loadCargo(plane);

    plane.boardPassengers(this->passengers);

    origin.planeDeparture(plane);
    // do some processing here...

    // pass the time

    destination.landPlane(plane);

    //TODO: what to do here with the passengers
    plane.unboardPassengers();

    destination.offloadCargo(plane);
}