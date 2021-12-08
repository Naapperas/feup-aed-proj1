//
// Created by naapperas on 05/12/21.
//

#ifndef AED2122PROJ_TICKET_H
#define AED2122PROJ_TICKET_H

#include "./passenger.h"

class Ticket {

        Passenger p;
    public:
        Ticket(const Passenger& p) : p(p) {}

        const Passenger& getPassenger() const {
            return this->p;
        };
};

#endif //AED2122PROJ_TICKET_H
