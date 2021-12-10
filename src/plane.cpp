//
// Created by naapperas on 03/12/21.
//

#include "../includes/plane.h"

void Plane::addPassenger(const Passenger &passenger) {
    this->planePassengers.emplace_back(passenger);
}

void Plane::addLuggage(const Luggage &planeLuggage) {
    this->planeLuggage.emplace_back(planeLuggage);
}

bool operator==(const Plane& a, const Plane& b) { // required for lists to work
    return a.getPlate() == b.getPlate();
}