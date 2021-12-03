#include <iostream>

#include "./includes/plane.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Plane* p = new Plane("Plane", 500);
    Flight* f = new Flight(876234, "", "", "", 300, p);

    p->addFlightToPlan(f);

    delete p;

    return 0;
}
