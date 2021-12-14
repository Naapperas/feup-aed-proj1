//
// Created by Utilizador on 07/12/2021.
//

#ifndef AED2122PROJ_CARRIAGE_H
#define AED2122PROJ_CARRIAGE_H

#include <string>
#include <stack>
#include <vector>
#include <list>

#include "./luggage.h"

using namespace std;

class Carriage{
    const unsigned numberStacks;
    const unsigned stackCapacity;
    vector<stack<Luggage>> carriage;

    bool stackFull(unsigned& i) const{
        return carriage[i].size() == stackCapacity;
    }

    void emptyStack(unsigned& i, std::list<Luggage>& ret){
        while (!carriage[i].empty()){
            ret.push_back(carriage[i].top());
            carriage[i].pop();
        }
    }

public:
    Carriage(unsigned numberStacks, unsigned stackCapacity) : numberStacks(numberStacks), stackCapacity(stackCapacity) {}
    unsigned freeStack() const;
    void addLuggage(const Luggage& luggage);
    bool carriageFull() const;
    void removeLuggage(std::list<Luggage>& tmp);
};

#endif //AED2122PROJ_CARRIAGE_H
