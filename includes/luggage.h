//
// Created by naapperas on 01/12/21.
//

#ifndef AED2122PROJ_LUGGAGE_H
#define AED2122PROJ_LUGGAGE_H

#include <vector>
#include <algorithm>

class Luggage {

        static int CURRENT_LUGGAGE_ID;
        int id;
        static std::vector<Luggage*> items;

    public:
        Luggage() : id(CURRENT_LUGGAGE_ID++) {
            items.push_back(this);
        }

        int getId() const {
            return this->id;
        }

        static const Luggage& getLuggage(int luggageId);

};

#endif //AED2122PROJ_LUGGAGE_H
