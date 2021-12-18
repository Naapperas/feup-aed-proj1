//
// Created by naapperas on 05/12/21.
//

#include "../includes/flight.h"

long Flight::CURRENT_FLIGHT_NUMBER = 1;

bool Flight::addPassenger(Ticket* ticket) {
    if (this->lotation < this->getPlane()->getCapacity()) {
        this->tickets.emplace_back(ticket);
        this->lotation++;
        return true;
    }
    return false;
}

bool Flight::addPassengers(const std::vector<Ticket*>& tickets) {
    if (this->lotation + tickets.size() < this->getPlane()->getCapacity()) {
        for (auto ticket : tickets)
            this->addPassenger(ticket);
        return true;
    }
    return false;
}

bool Flight::execute() {

    auto originAirport = this->getOriginAirport(), destinationAirport = this->getDestinationAirport();
    auto flightPlane = this->getPlane();

    if (!originAirport->planeIsLanded(flightPlane))
        return false;

    for (auto ticket : this->tickets)
        originAirport->addLuggageToTransportBelt(ticket->getPassenger()->getLuggage());

    originAirport->loadCargo(flightPlane);

    std::vector<Passenger*> passengers;
    for (auto ticket : this->tickets)
        passengers.push_back(ticket->getPassenger());

    flightPlane->boardPassengers(passengers);

    originAirport->planeDeparture(flightPlane);
    // do some processing here...

    // pass the time

    destinationAirport->landPlane(flightPlane);

    //TODO: what to do here with the passengers
    flightPlane->unboardPassengers();

    destinationAirport->offloadCargo(flightPlane);

    return true;
}