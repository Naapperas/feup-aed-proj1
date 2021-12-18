//
// Created by Utilizador on 07/12/2021.
//

#ifndef AED2122PROJ_LUGGAGETRANSPORT_H
#define AED2122PROJ_LUGGAGETRANSPORT_H

#include <vector>
#include <list>

#include "luggage.h"
#include "carriage.h"

class LuggageTransport {
    unsigned numberStacks, stackCapacity;
    std::list<Carriage*> carriages;
    unsigned numberCarriages;
    friend ostream& operator <<(std::ostream& out , const LuggageTransport &a);
public:

    /**
     * Creates a new luggage transport system
     * @param numberStacks Number of stacks for carriage
     * @param stackCapacity Number of pieces each stack can take
     */
    LuggageTransport(unsigned numberStacks, unsigned stackCapacity) : numberStacks(numberStacks), stackCapacity(stackCapacity){
        addCarriage();
    }

    ~LuggageTransport() {
        for (auto carriage : this->carriages)
            delete carriage;
    }

    /**
     * When the luggage transport system gets full, add a new carriage
     */
    void addCarriage();


    void addLuggage(Luggage* luggage);

    /**
     * Besides clearing each carriage the system uses, it only leaves the system with one empty carriage
     * @return Returns the luggage of the passengers so it can be loaded into the plane
     */
    std::list<Luggage*> getCargo();
};

#endif //AED2122PROJ_LUGGAGETRANSPORT_H
