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
            PLANE = 1,
            ADMIN_FLIGHT,
            ADMIN_BACK
        };

        enum ClientMenuOption {
            TICKET = 1,
            BOARD,
            CLIENT_FLIGHTS,
            CLIENT_BACK
       };

    public:

        static void init();

        static int showInitialMenu(const std::string& airlineName);
        static int showAdminMenu();
        static int showClientMenu();
        static void endProgram();

};

#endif //AED2122PROJ_MENU_H
