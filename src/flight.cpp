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

    auto &originAirport = this->getOriginAirport(), &destination = this->getDestinationAirport();
    auto &flightPlane = this->getPlane();

    for (auto& passenger : this->passengers)
        originAirport.addLuggageToTransportBelt(passenger.getLuggage());

    originAirport.loadCargo(flightPlane);

    flightPlane.boardPassengers(this->passengers);

    originAirport.planeDeparture(flightPlane);
    // do some processing here...

    // pass the time

    destination.landPlane(flightPlane);

    //TODO: what to do here with the passengers
    flightPlane.unboardPassengers();

    destination.offloadCargo(flightPlane);
}