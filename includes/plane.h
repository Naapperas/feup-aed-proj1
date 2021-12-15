//
// Created by naapperas on 01/12/21.
//

#ifndef AED2122PROJ_PLANE_H
#define AED2122PROJ_PLANE_H

#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>

#include "passenger.h"
#include "luggage.h"

/**
 * Represents a maintenance/cleaning service that can be performed on a plane.
 */
class CleaningService {

    public:
        enum ServiceType {
            MAINTENANCE,
            CLEANING
        };
    private:
        ServiceType serviceType;
        std::string serviceDate, employee;
        static const std::vector<std::string> typePrint;
        friend std::ostream& operator <<(std::ostream& out ,const CleaningService & a);
    public:
        CleaningService(ServiceType serviceType, const std::string& serviceDate, const std::string& employee) :
        serviceType(serviceType), serviceDate(serviceDate), employee(employee) {}

};

/**
 * Represents an airship that can be used to perform a flight.
 */
class Plane {

        std::string type, plate;
        unsigned capacity, cargoCapacity;

        std::deque<CleaningService> upcomingCleaningTasks, pastCleaningTasks;

        // this should provide fast insertion removal (simulating transporting passengers + cargo, we don't care about searching them)
        std::list<Passenger> planePassengers;
        std::list<Luggage> planeLuggage;

        /**
         * Deletes a register of a cleaning service from the dedicated file
         * @param service cleaning service to be removed
         */
        void deleteRegisterCleaningService(const CleaningService& service);

        friend bool operator==(const Plane& a, const Plane& b);
        friend std::ostream& operator <<(std::ostream& out ,const Plane& a);
    public:
        /**
         * Creates a plane.
         *
         * @param type the type of the plane
         * @param planePlate the plate associated with this plane
         * @param planeCapacity the capacity of this plane
         * @param cargoCapcity the cargoCapacity of this plane
         */
        Plane(const std::string& type, const std::string& planePlate, unsigned planeCapacity, unsigned cargoCapcity) : type(type), plate(planePlate), capacity(planeCapacity), cargoCapacity(cargoCapcity) {}

        /**
         * Returns the type of this airship.
         *
         * @return the type of this airship
         */
        const std::string& getType() const {
            return type;
        }

        /**
         * Returns the plate of this airplane.
         *
         * @return the plate of this airplane
         */
        const std::string& getPlate() const {
            return plate;
        }

        /**
         * Returns the capacity of this plane.
         *
         * @return the capacity of this plane
         */
        unsigned int getCapacity() const {
            return capacity;
        }

        /**
         * Adds a cleaning service to be performed on this plane.
         *
         * @param cleaningService the cleaning service to be performed on this plane
         */
        void addCleaningService(const CleaningService& cleaningService) {
            upcomingCleaningTasks.push_back(cleaningService);
        }

        /**
         * Register a cleaning service to it's dedicated file
         * To be used together with addCleaningService
         * @param cleaningService cleaning service to be registered
         */
        void registerCleaningservice(const CleaningService& cleaningService){
            std::ofstream serviceFile{"cleaning.txt"};
            serviceFile  << this->plate <<  " " << cleaningService;
        }

        /**
         * Finishes a pre-scheduled cleaning service.
         */
        void finishedCleaningService() {
            pastCleaningTasks.push_back(upcomingCleaningTasks.front()); // archive finished cleaning/maintenence service
            deleteRegisterCleaningService(upcomingCleaningTasks.front()); // delete finished service from file
            upcomingCleaningTasks.pop_front(); // erase from deque
        }


        void addLuggage(const Luggage& planeLuggage);
        void addPassenger(const Passenger& passenger);

        /**
         * Boards the given collection of passengers on the plane.
         *
         * @param passengers the passengers to board
         */
        void boardPassengers(std::vector<Passenger>& passengers);

        /**
         * Unboards this plane's passengers.
         */
        void unboardPassengers();

};

#endif //AED2122PROJ_PLANE_H
