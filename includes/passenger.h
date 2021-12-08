//
// Created by naapperas on 01/12/21.
//

#ifndef AED2122PROJ_PASSENGER_H
#define AED2122PROJ_PASSENGER_H

#include <string>

#include "./luggage.h"

class Passenger {

    std::string name;
    unsigned age; // don't know if it's necessary
    Luggage l; // optional
public:

    Passenger(const std::string& name, unsigned age) : name(name), age(age) {}

    Passenger(const std::string& name, unsigned age, const Luggage& luggage) : Passenger(name, age) {
        this->l = luggage;
    }

    std::string getName() const{
        return this->name;
    }

    unsigned getAge() const{
        return this->age;
    }

    const Luggage& getLuggage() const {
        return this->l;
    };
};

#endif //AED2122PROJ_PASSENGER_H
