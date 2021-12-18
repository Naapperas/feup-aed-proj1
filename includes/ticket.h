//
// Created by naapperas on 05/12/21.
//

#ifndef AED2122PROJ_TICKET_H
#define AED2122PROJ_TICKET_H

#include "./passenger.h"

class Ticket {

        Passenger* p = nullptr;
    public:
        Ticket(Passenger* p) : p(p) {}

        ~Ticket() {
            if (p != nullptr)
                delete p;
        }

        Passenger* getPassenger() const {
            return this->p;
        };
};

#endif //AED2122PROJ_TICKET_H
