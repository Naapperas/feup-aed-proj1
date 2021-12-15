//
// Created by naapperas on 03/12/21.
//

#include "../includes/plane.h"


const std::vector<std::string> CleaningService::typePrint = {"Maintenance", "Cleaning"};

std::ostream& operator <<(std::ostream& out , const CleaningService &a) {
    out << a.typePrint.at(a.serviceType) << " " << a.serviceDate << " " << a.employee << '\n';
    return out;
}

void Plane::deleteRegisterCleaningService(const CleaningService &service) {
    std::queue<std::string> servicesToKeep;
    std::string serviceToRemove;
    serviceToRemove += this->plate + " ";
    std::stringstream ss;
    ss << service;
    serviceToRemove += ss.str();
    std::ifstream serviceFile{"cleaning.txt"};
    while(!serviceFile.eof()){
        std::string currentService;
        getline(serviceFile, currentService);
        if (currentService!=serviceToRemove)
            servicesToKeep.push(currentService);
    }
    serviceFile.close();
    while(!servicesToKeep.empty()){
        std::ofstream serviceFileWrite{"cleaning.txt"};
        serviceFileWrite << servicesToKeep.front() << '\n';
        servicesToKeep.pop();
    }
}

void Plane::addPassenger(const Passenger &passenger) {
    this->planePassengers.emplace_back(passenger);
}

void Plane::addLuggage(const Luggage &planeLuggage) {
    this->planeLuggage.emplace_back(planeLuggage);
}

void Plane::boardPassengers(std::vector<Passenger> &passengers) {
    for (const auto& passenger : passengers)
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

