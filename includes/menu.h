//
// Created by naapperas on 14/12/21.
//

#ifndef AED2122PROJ_MENU_H
#define AED2122PROJ_MENU_H

#include "airline.h"

class Menu {

        static std::string AIRLINE_ADMIN_PASSWORD;

        static bool exitApplication;

        enum MainMenuOption {
            CLIENT = 1,
            ADMIN,
            LEAVE
        };

        enum AdminMenuOption {
            PURCHASE_PLANE = 1,
            ADMIN_CREATE_FLIGHT,
            ADMIN_DELETE_FLIGHT,
            ADMIN_PLANES,
            ADMIN_LAND_TRANSPORT_PLACE,
            ADMIN_BACK
        };

        enum ClientMenuOption {
            TICKET = 1,
            BOARD,
            CLIENT_FLIGHTS,
            CLIENT_BACK
       };

        static void waitForPrompt(const std::string& prompt);

    public:

        static void init();

        static int showInitialMenu(const std::string& airlineName);
        static int showAdminMenu();
        static int showClientMenu();
        static void endProgram();
        static void listFlights();
        static void listPlanes();
        static void purchasePlane();
        static void registerTransportPlace();
        static void createFlight();
        static void cancelFlight();
};

#endif //AED2122PROJ_MENU_H
