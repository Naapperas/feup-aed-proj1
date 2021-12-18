//
// Created by Utilizador on 14/12/2021.
//

#include <iostream>
#include "../includes/carriage.h"

unsigned Carriage::freeStack() const{
    for (unsigned i = 0; i < numberStacks; i++){
        if (!stackFull(i))
            return i;
    }

    return -1; // full Carriage
}

void Carriage::addLuggage(Luggage* luggage){
    auto freeStack = this->freeStack();

    if (freeStack != -1) {
        carriage[freeStack].push(luggage);
    }
    else
        throw std::string("Full Carriage");
}

bool Carriage::carriageFull() const{
    for (unsigned i = 0; i < numberStacks; i++){
        if (!stackFull(i))
            return false;
    }

    return true;
}

void Carriage::removeLuggage(std::list<Luggage*>& tmp){
    for (unsigned i = 0; i < numberStacks; i++) {
        emptyStack(i, tmp);
    }
}

