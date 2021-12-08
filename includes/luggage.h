//
// Created by naapperas on 01/12/21.
//

#ifndef AED2122PROJ_LUGGAGE_H
#define AED2122PROJ_LUGGAGE_H

/**
 * Luggage that can be carried arround or be owned by a passenger.
 */
class Luggage {

    // no useful data on luggages ?

    friend bool operator==(const Luggage& a, const Luggage& b) { return &a == &b; };

    public:
        Luggage() {}

};

#endif //AED2122PROJ_LUGGAGE_H
