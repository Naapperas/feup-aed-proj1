//
// Created by naapperas on 14/12/21.
//


#include "../includes/luggageTransport.h"

void LuggageTransport::addLuggage(const Luggage& luggage){
    bool addedLuggage = false;

    for(auto carriage : carriages){
        if (!carriage.carriageFull()) {
            carriage.addLuggage(luggage);
            addedLuggage = true;
            break;
        }
    }

    if (!addedLuggage){
        this->addCarriage();
        carriages[carriages.size() - 1].addLuggage(luggage);
    }
}

std::list<Luggage> LuggageTransport::getCargo() {
    std::list<Luggage> tmp;

    for (auto& carriage : this->carriages) {

        auto carriageCargo = carriage.removeLuggage();

        for (auto& lugagage : carriageCargo)
            tmp.push_back(lugagage);
    }

    return tmp;
};