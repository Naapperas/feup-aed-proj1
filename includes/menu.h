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
            ADMIN_RESCHEDULE_FLIGHT,
            ADMIN_PLANES,
            ADMIN_AIRPORT_REGISTER,
            ADMIN_LAND_TRANSPORT_PLACE,
            ADMIN_LAND_TRANSPORT_PLACE_UPDATE,
            ADMIN_CLEANING_SERVICE,
            ADMIN_BACK
        };

        enum ClientMenuOption {
            TICKET = 1,
            CLIENT_FLIGHTS,
            CLIENT_TRANSPORTS,
            CLIENT_BACK
       };

        /**
         * Waits for user input (new line) to progress
         * @param prompt
         */
        static void waitForPrompt(const std::string& prompt);

    public:
        /**
         * Initialize the program
         */
        static void init();

        /**
         * Shows the initial menu on screen
         * @param airlineName Name of the airline we are managing (displayed on screen)
         * @return User option (Client/Admin/EXit)
         */
        static int showInitialMenu(const std::string& airlineName);
        /**
         * Shows the administrator menu on screen
         * @return User option (from the admin functionalities available)
         */
        static int showAdminMenu();
        /**
         * Shows the administrator menu on screen
         * @return User option (from the client functionalities available)
         */
        static int showClientMenu();

        /**
         * Close the program
         */
        static void endProgram();

        static void buyTickets();
        static void listFlights();
        static void listTransportPlaces();
        static void listPlanes();
        static void purchasePlane();
        static void registerAirport();
        static void registerTransportPlace();
        static void updateTransportPlace();
        static void createFlight();
        static void cancelFlight();
        static void rescheduleFlight();
        static void addCleaningService();
};

#endif //AED2122PROJ_MENU_H
