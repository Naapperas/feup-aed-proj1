//
// Created by Utilizador on 07/12/2021.
//

#ifndef AED2122PROJ_CARRIAGE_H
#define AED2122PROJ_CARRIAGE_H

#include <stack>
#include <vector>

#include "./luggage.h"

using namespace std;

class Carriage{
    const unsigned numberStacks;
    const unsigned stackCapacity;
    vector<stack<Luggage*>> carriage;
public:
    Carriage(unsigned numberStacks, unsigned stackCapacity) : numberStacks(numberStacks), stackCapacity(stackCapacity) {}

    bool stackFull(unsigned& i) const{
        return carriage[i].size() == stackCapacity;
    }

    unsigned freeStack() const{
        for (unsigned i = 0; i < numberStacks; i++){
            if (!stackFull(i))
                return i;
        }

        return -1; // full Carriage
    }

    void addLuggage(Luggage* luggage){
        if (freeStack() != -1)
            carriage[freeStack()].push(luggage);
        else
            throw "Full Carriage";
    }

    bool carriageFull() const{
        for (unsigned i = 0; i < numberStacks; i++){
            if (!stackFull(i))
                return false;
        }

        return true;
    }
};

#endif //AED2122PROJ_CARRIAGE_H
