//
// Created by naapperas on 01/12/21.
//

#ifndef AED2122PROJ_PLANE_H
#define AED2122PROJ_PLANE_H

#include <vector>
#include <deque>
#include <list>
#include <string>

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
        CleaningService(ServiceType serviceType, const std::string& serviceDate, const std::string& employee) :
        serviceType(serviceType), serviceDate(serviceDate), employee(employee) {}

};

class Plane {

        std::string type, plate;
        unsigned capacity;

        std::deque<CleaningService> upcomingCleaningTasks, pastCleaningTasks;
    public:
        Plane(const std::string& type, const std::string& planePlate, unsigned planeCapacity) : type(type), plate(planePlate), capacity(planeCapacity) {}

        const std::string& getType() {
            return type;
        }

        const std::string& getPlate() const {
            return plate;
        }

        unsigned int getCapacity() const {
            return capacity;
        }

        void addCleaningService(const CleaningService& cleaningService) {
            upcomingCleaningTasks.push_back(cleaningService);
        }

        void finishedCleaningService() {
            pastCleaningTasks.push_back(upcomingCleaningTasks.front()); // archive finished cleaining/maintenence service
            upcomingCleaningTasks.pop_front(); // erase from deque
        }
};

#endif //AED2122PROJ_PLANE_H
