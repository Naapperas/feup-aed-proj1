//
// Created by naapperas on 01/12/21.
//

#ifndef AED2122PROJ_PASSENGER_H
#define AED2122PROJ_PASSENGER_H

#include <string>

#include "./luggage.h"

/**
 * Represents a passenger of the airline.
 */
class Passenger {

    std::string name;
    unsigned age; // don't know if it's necessary
    Luggage* l = nullptr; // optional
public:

    /**
     * Creates a passenger without luggage.
     *
     * @param name the name of this passenger
     * @param age the age of this passenger
     */
    Passenger(const std::string& name, unsigned age) : name(name), age(age) {}

    /**
     * Creates a passenger witrh the given luggage.
     *
     * @param name the name of this passenger
     * @param age the age of this passenger
     * @param luggage the luggage owned by this passenger
     */
    Passenger(const std::string& name, unsigned age, Luggage* luggage) : Passenger(name, age) {
        this->l = luggage;
    }

    ~Passenger() {
        if (l != nullptr)
            delete l;
    }

    /**
     * Returns the name of this passenger.
     *
     * @return the name of this passenger
     */
    std::string getName() const{
        return this->name;
    }

    /**
     * Returns the age of this passenger.
     *
     * @return the age of this passenger
     */
    unsigned getAge() const{
        return this->age;
    }

    /**
     * Returns the luggage owned by this pasenger.
     *
     * @return the luggage owned by this passenger
     */
    Luggage* getLuggage() const {
        return this->l;
    };

    /**
     * Checks if this passanger has luggage assined to him.
     *
     * @return weather this passenger has luggage or not
     */
    bool hasLuggage() const {
        return this->getLuggage() != nullptr;
    }
};

#endif //AED2122PROJ_PASSENGER_H
