//
// Created by naapperas on 05/12/21.
//

#ifndef AED2122PROJ_TICKET_H
#define AED2122PROJ_TICKET_H

#include "./passenger.h"

/**
 * Class representing a buyable ticket to a flight.
 */
class Ticket {

        Passenger* p = nullptr;
    public:

        /**
         * Creates a ticket that was bought by the given passenger.
         *
         * @param p the passenger that bought this ticket
         */
        Ticket(Passenger* p) : p(p) {}

        ~Ticket() {
            if (p != nullptr)
                delete p;
        }

        /**
         * Get the passenger that owns this ticket.
         *
         * @return passenger that owns this ticket
         */
        Passenger* getPassenger() const {
            return this->p;
        };
};

#endif //AED2122PROJ_TICKET_H
