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
    vector<stack<Luggage*>> carriage;

    /**
     *
     * @param index of the stack
     * @return Returns true, if stack still has space
     */
    bool stackFull(unsigned& i) const{
        return carriage[i].size() == stackCapacity;
    }

    /**
     * Clear´s the stack
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
     * @param numberStacks Number of stacks
     * @param stackCapacity Number of pieces each stack can take
     */
    Carriage(unsigned numberStacks, unsigned stackCapacity) : numberStacks(numberStacks), stackCapacity(stackCapacity) {
        this->carriage = vector<stack<Luggage*>>(numberStacks);
    }

    ~Carriage() {
        for (auto luggageStack : this->carriage) {
            while (luggageStack.size() > 0) {
                auto p = luggageStack.top();
                luggageStack.pop();
                delete p;
            }
        }
    }

    /**
     *
     * @return Return´s the index of a Stack that has space or -1 if the carriage is full
     */
    unsigned freeStack() const;

    void addLuggage(Luggage* luggage);

    /**
     *
     * @return Return true if carriage is full
     */
    bool carriageFull() const;

    /**
     * Clear´s the carriage
     * @param tmp List that holds the luggage
     */
    void removeLuggage(std::list<Luggage*>& tmp);
};

#endif //AED2122PROJ_CARRIAGE_H
