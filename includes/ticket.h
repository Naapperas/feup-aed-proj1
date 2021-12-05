//
// Created by naapperas on 05/12/21.
//

#ifndef AED2122PROJ_TICKET_H
#define AED2122PROJ_TICKET_H

#include <vector>
#include <string>

#include "./passenger.h"
#include "./flight.h"

class Ticket {

    static int CURRENT_TICKET_ID;
    int id;
    static std::vector<Ticket*> items;

    int flightId;
    int passengerId;
public:
    Ticket(int flightId, int passengerId) : id(CURRENT_TICKET_ID++), flightId(flightId), passengerId(passengerId) {
        items.push_back(this);
    }

    const Flight& getFlight() const;

    const Passenger& getPassenger() const;

    static const Ticket& getTicket(int ticketId);

};

#endif //AED2122PROJ_TICKET_H
