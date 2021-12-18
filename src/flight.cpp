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

std::pair<Airport, Airport> Flight::execute() {

    auto &originAirport = this->getOriginAirport(), &destinationAirport = this->getDestinationAirport();
    auto &flightPlane = this->getPlane();

    if (!originAirport.planeIsLanded(flightPlane))
        return std::make_pair(originAirport, destinationAirport);

    for (auto& passenger : this->passengers)
        originAirport.addLuggageToTransportBelt(passenger.getLuggage());

    originAirport.loadCargo(flightPlane);

    flightPlane.boardPassengers(this->passengers);

    originAirport.planeDeparture(flightPlane);
    // do some processing here...

    // pass the time

    destinationAirport.landPlane(flightPlane);

    flightPlane.unboardPassengers();

    destinationAirport.offloadCargo(flightPlane);

    return std::make_pair(originAirport, destinationAirport);
}