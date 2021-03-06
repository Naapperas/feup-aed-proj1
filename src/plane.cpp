//
// Created by naapperas on 03/12/21.
//

#include <iostream>

#include "../includes/plane.h"

const std::vector<std::string> Service::typePrint = {"Maintenance", "Cleaning"};

std::ostream& operator <<(std::ostream& out , const Service &a) {
    out << a.typePrint.at(a.serviceType) << " " << a.serviceDate << " " << a.employee << '\n';
    return out;
}

void Plane::addPassenger(Passenger *passenger) {
    this->planePassengers.emplace_back(passenger);
}

void Plane::addLuggage(Luggage *planeLuggage) {
    this->planeLuggage.emplace_back(planeLuggage);
}

void Plane::boardPassengers(const std::vector<Passenger*>& passengers) {
    for (const auto passenger : passengers)
        this->addPassenger(passenger);
}

void Plane::unboardPassengers() {
    this->planePassengers.clear();
}

bool operator==(const Plane& a, const Plane& b) { // required for lists to work
    return a.getPlate() == b.getPlate();
}

std::ostream& operator <<(std::ostream& out , const Plane &a) {
    out << a.type << " " << a.plate << " " << a.capacity << " " << a.cargoCapacity << '\n';
    return out;
}

void Plane::storeCleaningServices(std::ofstream& ofstream) {

    unsigned pastSize = this->pastTasks.size(), upcomingSize = upcomingTasks.size();
    ofstream << "[PAST CLEANING TASKS]\n";
    for (unsigned i = 0; i < pastSize; i++) {
        const Service& service = pastTasks.front();
        pastTasks.pop();
        ofstream << this->getPlate() << ' ' << service;
    }

    ofstream << "[UPCOMING CLEANING TASKS]\n";
    for (unsigned i = 0; i < upcomingSize; i++) {
        const Service& service = upcomingTasks.front();
        upcomingTasks.pop();
        ofstream << this->getPlate() << ' ' << service;
    }
}

void Plane::offLoadCargo() {
    this->planeLuggage.clear();
}

void Plane::performServices() {
    if (this->upcomingTasks.empty())
        return;
    while (isPast(this->upcomingTasks.front().getDate())) {
        this->finishedService();
        if (upcomingTasks.empty())
            break;
    }

}