//
// Created by naapperas on 01/12/21.
//

#ifndef AED2122PROJ_PASSENGER_H
#define AED2122PROJ_PASSENGER_H

#include <string>
#include <vector>

#include "./luggage.h"

class Passenger {

    static int CURRENT_PASSENGER_ID;
    int id;
    static std::vector<Passenger*> items;

    std::string name;
    unsigned age; // don't know if it's necessary
    int luggageId = -1; // optional
public:

    Passenger(std::string name, unsigned age) : id(CURRENT_PASSENGER_ID++), name(name), age(age) {
        items.push_back(this);
    }

    Passenger(std::string name, unsigned age, int luggageId) : Passenger(name, age) {
        this->luggageId = luggageId;
    }

    std::string getName() const{
        return this->name;
    }

    unsigned getAge() const{
        return this->age;
    }

    const Luggage& getLuggage() const;

    static const Passenger& getPassenger(int passengerId);
};

#endif //AED2122PROJ_PASSENGER_H
