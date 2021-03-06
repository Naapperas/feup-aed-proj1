//
// Created by naapperas on 14/12/21.
//

#include <iostream>

#include "../includes/menu.h"

std::string Menu::AIRLINE_ADMIN_PASSWORD = "toni";
bool Menu::exitApplication = false;

void Menu::init() {

    atexit(Menu::endProgram);

    while (!Menu::exitApplication) {

        std::cout << std::string(100, '\n');

        int option = Menu::showInitialMenu(Airline::getInstance().getName());

        switch (option) {
            case CLIENT:
            case ADMIN:

                if (option == CLIENT) {

                    option = Menu::showClientMenu();

                    switch (option) {
                        case TICKET:
                            Menu::buyTickets();
                            break;
                        case CLIENT_FLIGHTS:
                            Menu::listFlights();
                            break;
                        case CLIENT_TRANSPORTS:
                            Menu::listTransportPlaces();
                            break;
                        case CLIENT_BACK:
                            break;
                        default:
                            std::cout << "Invalid option, returning to main menu\n\n";
                            break;
                    }

                } else {

                    option = Menu::showAdminMenu();

                    switch (option) {
                        case PURCHASE_PLANE:
                            Menu::purchasePlane();
                            break;
                        case ADMIN_CREATE_FLIGHT:
                            Menu::createFlight();
                            break;
                        case ADMIN_DELETE_FLIGHT:
                            Menu::cancelFlight();
                            break;
                        case ADMIN_RESCHEDULE_FLIGHT:
                            Menu::rescheduleFlight();
                            break;
                        case ADMIN_PLANES:
                            Menu::listPlanes();
                            break;
                        case ADMIN_AIRPORT_REGISTER:
                            Menu::registerAirport();
                            break;
                        case ADMIN_LAND_TRANSPORT_PLACE:
                            Menu::registerTransportPlace();
                            break;
                        case ADMIN_LAND_TRANSPORT_PLACE_UPDATE:
                            Menu::updateTransportPlace();
                            break;
                        case ADMIN_CLEANING_SERVICE:
                            Menu::addCleaningService();
                            break;
                        case ADMIN_BACK:
                            break;
                        default:
                            std::cout << "Invalid option, returning to main menu\n\n";
                            break;
                    }
                }
                break;
            case LEAVE:
                Menu::exitApplication = true;
                break;
            default:
                std::cout << "\tInvalid option chosen!\n\n";
                break;
        }
    }
}

int Menu::showAdminMenu() {

    std::string password;
    std::cout << "\tEnter your password please: ";
    std::cin >> password;

    if (!std::cin)
        exit(0);

    if (password != Menu::AIRLINE_ADMIN_PASSWORD) {
        std::cout << "\tInvalid password, going back to main menu\n\n";
        return ADMIN_BACK;
    }

    std::cout << std::string(100, '\n');

    int option;

    std::cout << "\tHello administrator, what would you like to do?\n\n";
    std::cout << "\t[1] Purchase new plane\n\t[2] Create new flight\n\t[3] Cancel flight\n\t[4] Reschedule a flight\n\t[5] List current fleet\n\t[6] Register new airport\n\t[7] Register new transport place near an airport\n\t[8] Update Transport Place Schedule\n\t[9] Register new cleaning service\n\t[10] Back\n\n";
    std::cout << "\t> ";
    std::cin >> option;

    if (!std::cin)
        exit(0);

    std::cout.flush();

    return option;
}

int Menu::showClientMenu() {

    int option;

    std::cout << "\tHello client, what would you like to do?\n\n";
    std::cout << "\t[1] Purchase ticket\n\t[2] See all available flights\n\t[3] See the land transports near an airport\n\t[4] Back\n\n";
    std::cout << "\t> ";
    std::cin >> option;

    if (!std::cin)
        exit(0);

    std::cout.flush();

    return option;
}

int Menu::showInitialMenu(const std::string& airlineName) {

    int option;

    std::cout << "\t\tWelcome to " << airlineName << " airlines\n\n";
    std::cout << "\t[1] Client\n\t[2] Admin\n\t[3] Exit\n\n";
    std::cout << "\t> ";
    std::cin >> option;

    if (!std::cin)
        exit(0);

    std::cout.flush();

    return option;
}

void Menu::endProgram() {
    Menu::waitForPrompt("\tProgram terminated, see you soon :) [press ENTER to quit]");
}

void Menu::listFlights() {
    Airline::getInstance().listCurrentFlights(); // generate the call in menu, delegate it to Airline
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::listPlanes() {
    Airline::getInstance().listCurrentPlanes(); // generate the call in menu, delegate it to Airline
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::purchasePlane() {
    Airline::getInstance().purchasePlane();
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::registerAirport(){
    Airline::getInstance().registerAirport();
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::registerTransportPlace() {
    Airline::getInstance().registerTransportPlace();
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::updateTransportPlace() {
    Airline::getInstance().updateTransportPlace();
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::cancelFlight() {
    Airline::getInstance().cancelFlight();
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::createFlight() {
    Airline::getInstance().createFlight();
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::rescheduleFlight() {
    Airline::getInstance().rescheduleFlight();
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::waitForPrompt(const std::string &prompt) {
    std::cout << prompt << std::endl;
    std::cin.get();
    if (std::cin.peek() == '\n') std::cin.ignore(100, '\n'); // 100 chars should be enough to ignore
}

void Menu::buyTickets() {
    Airline::getInstance().purchaseTicket();
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::listTransportPlaces() {
    Airline::getInstance().listTransportPlaces();
    Menu::waitForPrompt("\t[press ENTER to continue]");
}

void Menu::addCleaningService() {
    Airline::getInstance().addCleaningService();
    Menu::waitForPrompt("\t[press ENTER to continue]");
}
