//
// Created by Utilizador on 07/12/2021.
//

#ifndef AED2122PROJ_LUGGAGETRANSPORT_H
#define AED2122PROJ_LUGGAGETRANSPORT_H

#include <vector>
#include <list>

#include "luggage.h"
#include "carriage.h"

class LuggageTransport{
    const unsigned numberStacks;
    const unsigned stackCapacity;
    std::vector<Carriage> carriages;
public:
    LuggageTransport(unsigned numberStacks, unsigned stackCapacity) : numberStacks(numberStacks), stackCapacity(stackCapacity){}

    void addCarriage() {
        carriages.push_back(Carriage(numberStacks, stackCapacity));
    }

    void addLuggage(const Luggage& luggage);

    std::list<Luggage> getCargo();

};

#endif //AED2122PROJ_LUGGAGETRANSPORT_H
