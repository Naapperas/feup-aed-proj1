//
// Created by naapperas on 05/12/21.
//

#include "../includes/ticket.h"

int Ticket::CURRENT_TICKET_ID = 1;

const Ticket& Ticket::getTicket(int ticketId) {
    auto ticket = std::find_if(Ticket::items.begin(), Ticket::items.end(), [ticketId](Ticket* t) { return t->id == ticketId; });

    if (ticket != Ticket::items.end())
        return *(*ticket);

    throw "No ticket with given id";
}

const Passenger& Ticket::getPassenger() const {
    try {
        return Passenger::getPassenger(this->passengerId);
    } catch (char* err) {
        // no passenger found, what happened?
        // should never enter this block, add just for safety

        throw "No passenger found for given ticket";
    }
}

const Flight& Ticket::getFlight() const {
    try {
        return Flight::getFlight(this->flightId);
    } catch (char* err) {
        // no flight found, what happened?
        // should never enter this block, add just for safety

        throw "No flight found for given ticket";
    }
}