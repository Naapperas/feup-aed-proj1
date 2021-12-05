//
// Created by naapperas on 05/12/21.
//

#include "../includes/luggage.h"

int Luggage::CURRENT_LUGGAGE_ID = 1;
std::vector<Luggage*> Luggage::items = std::vector<Luggage*>();

const Luggage& Luggage::getLuggage(int luggageId) {
    auto luggage = std::find_if(Luggage::items.begin(), Luggage::items.end(), [luggageId](Luggage* l) { return l->id == luggageId; });

    if (luggage != Luggage::items.end())
        return *(*luggage);

    throw "No luggage with given id";
}