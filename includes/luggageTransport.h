//
// Created by Utilizador on 07/12/2021.
//

#ifndef AED2122PROJ_LUGGAGETRANSPORT_H
#define AED2122PROJ_LUGGAGETRANSPORT_H

#include <vector>

#include "./carriage.h"

using namespace std;

class LuggageTransport{
    const unsigned numberStacks;
    const unsigned stackCapacity;
    vector<Carriage> carriages;
public:
    LuggageTransport(unsigned numberStacks, unsigned stackCapacity) : numberStacks(numberStacks), stackCapacity(stackCapacity){}

    void addCarriage(){
        carriages.push_back(new Carriage(numberStacks, stackCapacity));
    }

    void addLuggage(Luggage* luggage){
        bool addedLuggage = false;
        for(auto carriage : carriages){
            if (!carriage.carriageFull()) {
                carriage.addLuggage();
                addedLuggage = true;
            }
        }
        if (!addedLuggage){
            this->addCarriage();
            carriages[carriages.size() - 1].addLuggage();
        }
    }
};

#endif //AED2122PROJ_LUGGAGETRANSPORT_H
