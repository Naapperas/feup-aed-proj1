//
// Created by naapperas on 01/12/21.
//

#ifndef AED2122PROJ_PASSENGER_H
#define AED2122PROJ_PASSENGER_H

class Passenger {
    std::string name;
    unsigned age; // don't know if it's necessary
    bool Luggage;
public:
    Passenger(std::string name, unsigned age, bool Luggage) : name(name), age(age), Luggage(Luggage){}

    std::string getName() const{
        return this->name;
    }

    unsigned getAge() const{
        return this->age;
    }

    bool hasLuggage() const{
        return this->Luggage;
    }
};

#endif //AED2122PROJ_PASSENGER_H
