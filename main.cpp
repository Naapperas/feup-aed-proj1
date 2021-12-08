#include <iostream>

#include "./includes/plane.h"
#include "includes/airport.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Plane p1{"J900", "oupas", 800}, p2{"B550", "adeus", 300}, p3{"A340", "ola", 300};

    Airport a{"Porto"};
    a.landPlane(p1);
    a.landPlane(p2);
    a.landPlane(p3);

    return 0;
}
