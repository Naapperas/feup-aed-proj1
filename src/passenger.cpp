//
// Created by naapperas on 05/12/21.
//

#include "../includes/passenger.h"

int Passenger::CURRENT_PASSENGER_ID = 1;
std::vector<Passenger*> Passenger::items = std::vector<Passenger*>();

const Luggage& Passenger::getLuggage() const {
    if (this->luggageId == -1)
        throw "Passanger has no luggage";

    try {
        return Luggage::getLuggage(this->luggageId);
    } catch (char* err) {
        // no luggage found for the given user, what happened?
        // should never enter this block, add just for safety

        throw "Passanger with no luggage found";
    }
}

const Passenger& Passenger::getPassenger(int passengerId) {
    auto passenger = std::find_if(Passenger::items.begin(), Passenger::items.end(), [passengerId](Passenger* p) { return p->id == passengerId; });

    if (passenger != Passenger::items.end())
        return *(*passenger);

    throw "No passenger with given id";
}