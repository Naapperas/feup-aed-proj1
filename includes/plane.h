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

        std::string plate;
        unsigned capacity, lotation;

        std::vector<Flight*> flightPlan;
        std::deque<CleaningService> upcomingCleaningTasks, pastCleaningTasks;
    public:
        Plane(const std::string& planePlate, unsigned planeCapacity) : plate(planePlate), capacity(planeCapacity), lotation(0) {}

        virtual ~Plane() {
            for (auto flight : flightPlan)
                if (flight != nullptr)
                    delete flight;
            this->flightPlan.clear();
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

        unsigned increaseLotation() {
            lotation++;
        }

        void addCleaningService(CleaningService cleaningService) {
            upcomingCleaningTasks.push_back(cleaningService);
        }

        void finishedCleaningService() {
            pastCleaningTasks.push_back(upcomingCleaningTasks.front()); // archive finished cleaining/maintenence service
            upcomingCleaningTasks.pop_front(); // erase from deque
        }

        /**
         * Adds a flight to this plane's flight plan.
         *
         * @param flight a pointer to the new flight to add
         */
        void addFlightToPlan(Flight* flight) {
            this->flightPlan.push_back(flight);
        }

        bool getPassengerList(long flightNumber, std::vector<Passenger*>& planePassangers) const {

            auto flight_itr = std::find_if(this->flightPlan.begin(), this->flightPlan.end(), [flightNumber](Flight* flight) { return flight->getFlightNumber() == flightNumber; });

            if (flight_itr == this->flightPlan.end())
                return false;

            planePassangers.clear();

            auto flight = *flight_itr;

            for (auto passenger : flight->getPassengers())
                planePassangers.push_back(passenger);

            return true;
        }
};

#endif //AED2122PROJ_PLANE_H
