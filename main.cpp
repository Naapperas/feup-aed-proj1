#include <iostream>

#include "./includes/plane.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    int* i = new int(1);
    std::cout << (i == nullptr) << std::endl;
    delete i;
    std::cout << (i == nullptr) << std::endl;

    Plane p = Plane("Plane", 500);
    Flight f = Flight(876234, "", "", "", 300, &p);
    p.addFlightToPlan(&f);

    return 0;
}
