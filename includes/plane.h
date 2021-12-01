//
// Created by naapperas on 01/12/21.
//

#ifndef AED2122PROJ_PLANE_H
#define AED2122PROJ_PLANE_H

#include <vector>
#include <deque>

#include "./flight.h"

class CleaningService {

        enum ServiceType {
            MAINTENANCE,
            CLEANING
        };

        ServiceType serviceType;
        std::string serviceDate, employee;
    public:
        CleaningService(ServiceType serviceType, const std::string &serviceDate, const std::string &employee) : serviceType(
                serviceType), serviceDate(serviceDate), employee(employee) {}

};

class Plane {

        std::string plate;
        unsigned capacity, lotation;

        std::vector<Flight*> flightPlan;
        std::deque<CleaningService> upcomingCleaningTasks, pastCleaningTasks;
    public:
        Plane(const std::string& planePlate, unsigned planeCapacity) : plate(planePlate), capacity(planeCapacity), lotation(0) {}

        virtual ~Plane() {
            for (auto flight : flightPlan)
                if (flight != nullptr) delete flight;
        }

    const std::string getPlate() const {
            return plate;
        }

        unsigned int getCapacity() const {
            return capacity;
        }

        const std::vector<Flight*> getFlightPlan() const {
            return flightPlan;
        }

        unsigned getLotation() const {
            return lotation;
        }
};

#endif //AED2122PROJ_PLANE_H
