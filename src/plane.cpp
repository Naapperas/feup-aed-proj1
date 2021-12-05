//
// Created by naapperas on 03/12/21.
//

#include "../includes/plane.h"

int Plane::CURRENT_PLANE_ID = 1;
std::vector<Plane*> Plane::items = std::vector<Plane*>();

const Plane& Plane::getPlane(int planeId) {
    auto plane = std::find_if(Plane::items.begin(), Plane::items.end(), [planeId](Plane* p) { return p->id == planeId; });

    if (plane != Plane::items.end())
        return *(*plane);

    throw "No plane with given id";
}
