#include <iostream>

#include "includes/plane.h"
#include "includes/airport.h"
#include "includes/flight.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Plane p1{"J900", "oupas", 2}, p2{"B550", "adeus", 2}, p3{"A340", "ola", 2};

    Airport a{"Porto"};
    a.landPlane(p1);
    a.landPlane(p2);

    Airport b{"Lisbon"};
    b.landPlane(p3);

    Flight f{"today", 3600, p1, a, b};

    Passenger pass1{"Nuno", 19};
    Passenger pass2{"Afonso", 39};

    auto t1 = a.purchaseTicket(f, pass1);
    auto t2 = a.purchaseTicket(f, pass2);

    f.addPassenger(t1), f.addPassenger(t2);

    f.execute();

    return 0;
}
