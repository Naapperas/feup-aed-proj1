//
// Created by naapperas on 14/12/21.
//


#include <iostream>
#include "../includes/luggageTransport.h"

void LuggageTransport::addCarriage() {
    carriages.push_back(new Carriage(numberStacks, stackCapacity));
}

void LuggageTransport::addLuggage(Luggage* luggage){
    Carriage* lastCarriage = carriages.back();

    if (lastCarriage->carriageFull()) {
        this->addCarriage();
        carriages.back()->addLuggage(luggage);
    }
    else{
        lastCarriage->addLuggage(luggage);
    }
}

std::list<Luggage*> LuggageTransport::getCargo() {
    std::list<Luggage*> tmp;

    for (auto& carriage : this->carriages) {
        carriage->removeLuggage(tmp);
    }

    auto coiso = carriages.begin()++;

    while (coiso != carriages.end()) {

        auto carriage = *coiso++;

        delete carriage;
    }

    carriages.erase(carriages.begin()++, carriages.end());
    return tmp;
};

std::ostream& operator <<(std::ostream& out , const LuggageTransport &a) {
    out << "Each carriage has " << a.numberStacks << " stacks, each stack can fit up to " << a.stackCapacity << "pieces off luggage."<< '\n';
    return out;
}