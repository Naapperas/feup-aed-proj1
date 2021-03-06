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
#include <ctime>


#include "passenger.h"
#include "luggage.h"

/**
 * Represents a maintenance/cleaning service that can be performed on a plane.
 */
class Service {

    public:

        /**
         * Reperesents the type of service that can be performed on this aircraft.
         */
        enum ServiceType {
            MAINTENANCE,
            CLEANING
        };
    private:
        ServiceType serviceType;
        std::string serviceDate, employee;
        static const std::vector<std::string> typePrint;
        friend std::ostream& operator <<(std::ostream& out ,const Service & a);
    public:

        /**
         * Creates a new service of the specified type, to be performed by the given employee on the given date.
         *
         * @param serviceType the type of service to perform
         * @param serviceDate the date to erform the given service
         * @param employee the person responsible for performing the given service
         */
        Service(ServiceType serviceType, const std::string& serviceDate, const std::string& employee) :
        serviceType(serviceType), serviceDate(serviceDate), employee(employee) {}

        /**
         * Get the date of this service
         * @return the date of this service
         */
        std::string getDate() const{
            return this->serviceDate;
        }
};

/**
 * Represents an airship that can be used to perform a flight.
 */
class Plane {

        std::string type, plate;
        unsigned capacity, cargoCapacity;

        std::queue<Service> upcomingTasks, pastTasks;

        // this should provide fast insertion removal (simulating transporting passengers + cargo, we don't care about searching them)
        std::list<Passenger*> planePassengers;
        std::list<Luggage*> planeLuggage;

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
         * @return true if added successfully (date is after the last added service's date
         */
        bool addService(const Service& cleaningService) {
            if (upcomingTasks.empty()){
                upcomingTasks.push(cleaningService);
                return true;
            } else if (cleaningService.getDate() > upcomingTasks.back().getDate()) {
                upcomingTasks.push(cleaningService);
                return true;
            } else
                return false;
        }

        /**
         * Finishes a pre-scheduled cleaning service.
         */
        void finishedService() {
            pastTasks.push(upcomingTasks.front());
            upcomingTasks.pop();
        }

        /**
         * Add luggage that will be carried in this flight
         * @param planeLuggage luggage that will be carried in this flight
         */
        void addLuggage(Luggage* planeLuggage);

        /**
         * Add a passenger that will be boarding this flight
         * @param passenger passenger that will be boarding this flight
         */
        void addPassenger(Passenger* passenger);

        /**
         * Boards the given collection of passengers on the plane.
         *
         * @param passengers the passengers to board
         */
        void boardPassengers(const std::vector<Passenger*>& passengers);

        /**
         * Unboards this plane's passengers.
         */
        void unboardPassengers();

        /**
         * Unload luggage from the plane
         */
        void offLoadCargo();

        /**
         * Serializes this plane's services to the given file.
         *
         * @param ofstream the file stream to which the services are written
         */
        void storeCleaningServices(std::ofstream& ofstream);

        /**
         * Performs the past services sheduled for this plane.
         */
        void performServices();

        /**
         * Compares the given cleaning task date against the current time
         *
         * @param serviceDate the service date
         * @return true if the given date is prior to the current date
         */
        static bool isPast(std::string serviceDate) {

            time_t now = time(0);
            tm *currentDateTime = gmtime(&now);

            int day, month, year;
            char delim;

            std::stringstream ss{serviceDate};
            ss >> year >> delim >> month >> delim >> day;

            if (year == (1900 + currentDateTime->tm_year))
                if (month == (currentDateTime->tm_mon+1))
                    return day < currentDateTime->tm_mday;
                else
                    return month < (currentDateTime->tm_mon+1);
            else
                return year < (1900 + currentDateTime->tm_year);
        }
};

#endif //AED2122PROJ_PLANE_H
