#include <iostream>

#include "includes/menu.h"

int main() {

    //TODO: intialization code

    Airline ourAirline{"Bogos-binted"};
    Airline::setInstance(&ourAirline);

    Menu::init();

    return 0;
}
