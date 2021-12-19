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

/**
 * Represents a luggage carriage that can be chained into a bigger LuggageTransport entity
 */
class Carriage{
    const unsigned numberStacks;
    const unsigned stackCapacity;
    vector<stack<Luggage*>> carriage;

    /**
     * Checks if a stack is full or not
     *
     * @param index of the stack
     * @return Returns true, if stack still has space
     */
    bool stackFull(unsigned& i) const{
        return carriage[i].size() == stackCapacity;
    }

    /**
     * Clears the stack at index 'i'
     *
     * @param i index of the stack
     * @param ret list that holds the luggage
     */
    void emptyStack(unsigned& i, std::list<Luggage*>& ret){
        while (!carriage[i].empty()){
            ret.push_back(carriage[i].top());
            carriage[i].pop();
        }
    }

public:

    /**
     * Creates a new carriage
     *
     * @param numberStacks Number of stacks
     * @param stackCapacity Number of pieces each stack can take
     */
    Carriage(unsigned numberStacks, unsigned stackCapacity) : numberStacks(numberStacks), stackCapacity(stackCapacity) {
        this->carriage = vector<stack<Luggage*>>(numberStacks);
    }

    ~Carriage() {
        for (auto luggageStack : this->carriage) {
            while (luggageStack.size() > 0) {
                auto p = luggageStack.top(); // redundant, since we always exhaust the luggage carriages
                luggageStack.pop();
                delete p;
            }
        }
    }

    /**
     * Looks for the next freeStack in which we can place luggages.
     *
     * @return Return´s the index of a Stack that has space or -1 if the carriage is full
     */
    unsigned freeStack() const;

    /**
     * Place luggage on this carriage.
     *
     * @param luggage Luggage to be added
     */
    void addLuggage(Luggage* luggage);

    /**
     * Checs if a given carriage is filled up to its maximum.
     *
     * @return Return true if carriage is full
     */
    bool carriageFull() const;

    /**
     * Removes the luggage from this carriage, placing it in tmp
     *
     * @param tmp List that holds the luggage
     */
    void removeLuggage(std::list<Luggage*>& tmp);
};

#endif //AED2122PROJ_CARRIAGE_H
