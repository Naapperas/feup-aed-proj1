#include <iostream>

#include "./includes/luggage.h"
#include "./includes/passenger.h"
#include "./includes/ticket.h"
#include "./includes/plane.h"
#include "./includes/airport.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Luggage l = Luggage();
    Passenger p = Passenger("Nuno", 19, l.getId());

    Plane pl = Plane("A307", "33-ER-44", 200);

    Flight f = Flight(123456789, "amanhã", "ali", "aqui", 1, pl.getId());

    Ticket t = Ticket(f.getId(), p.getId());


    std::ifstream aaa("Porto.txt");
    Airport a("Porto", aaa);
    //Airport a("Porto");

    a.printTransportPlaces();



    return 0;
}
