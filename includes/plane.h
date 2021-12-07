//
// Created by naapperas on 01/12/21.
//

#ifndef AED2122PROJ_PLANE_H
#define AED2122PROJ_PLANE_H

#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <string>

#include "./flight.h"
#include "./passenger.h"

class CleaningService {

    public:
        enum ServiceType {
            MAINTENANCE,
            CLEANING
        };
    private:
        ServiceType serviceType;
        std::string serviceDate, employee;
    public:
        CleaningService(ServiceType serviceType, const std::string &serviceDate, const std::string &employee) : serviceType(
                serviceType), serviceDate(serviceDate), employee(employee) {}

};

class Plane {

        static int CURRENT_PLANE_ID;
        int id;
        static std::vector<Plane*> items;

        std::string type, plate;
        unsigned capacity;

        std::vector<int> flightPlan;
        std::deque<CleaningService> upcomingCleaningTasks, pastCleaningTasks;
    public:
        Plane(const std::string& type, const std::string& planePlate, unsigned planeCapacity) : id(CURRENT_PLANE_ID++), type(type), plate(planePlate), capacity(planeCapacity) {
            items.push_back(this);
        }

        const std::string& getPlate() const {
            return plate;
        }

        unsigned int getCapacity() const {
            return capacity;
        }

        const std::vector<int>& getFlightPlan() const {
            return flightPlan;
        }

        void addCleaningService(const CleaningService& cleaningService) {
            upcomingCleaningTasks.push_back(cleaningService);
        }

        void finishedCleaningService() {
            pastCleaningTasks.push_back(upcomingCleaningTasks.front()); // archive finished cleaining/maintenence service
            upcomingCleaningTasks.pop_front(); // erase from deque
        }

        // mark as no discard because we always want to use a given object's id for something
        [[nodiscard]]
        int getId() const {
            return this->id;
        }

        static const Plane& getPlane(int planeId);
};

#endif //AED2122PROJ_PLANE_H
