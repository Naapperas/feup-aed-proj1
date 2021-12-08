//
// Created by naapperas on 05/12/21.
//

#include "../includes/flight.h"

long Flight::CURRENT_FLIGHT_NUMBER = 1;

void Flight::addPassenger(const Ticket& ticket) {
    if (this->lotation < this->getPlane().getCapacity()) {
        this->passengers.emplace_back(ticket.getPassenger());
        this->lotation++;
    }
}

void Flight::addPassengers(const std::vector<Ticket>& tickets) {
    if (this->lotation + tickets.size() < this->getPlane().getCapacity()) {
        for (auto ticket : tickets)
            this->addPassenger(ticket);
    }
}