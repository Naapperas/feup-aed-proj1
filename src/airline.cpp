//
// Created by naapperas on 13/12/21.
//
#include <algorithm>
#include <fstream>
#include <sstream>

#include "../includes/airline.h"

Airline::Airline(const std::string &name) : airlineName(name) {

    // initialize ownedPlanes
    std::ifstream planeFile{"planes.txt"};
    if (!planeFile.is_open())
        std::ofstream planeFileNew{"planes.txt"};
    else{
        while(!planeFile.eof()){
            std::string currentPlane;
            getline(planeFile,currentPlane);
            std::stringstream ss(currentPlane);
            std::string type, plate;
            unsigned capacity, cargoCapacity;
            ss >> type >> plate >> capacity >> cargoCapacity;
            ownedPlanes.push_back(Plane(type, plate, capacity, cargoCapacity));
        }
    }

    // initialize cleaning services for owned planes
    std::ifstream serviceFile{"cleaning.txt"};
    if (!planeFile.is_open())
        std::ofstream serviceFileNew{"cleaning.txt"};
    else{
        while(!serviceFile.eof()){
            std::string currentService;
            getline(serviceFile,currentService);
            std::stringstream ss(currentService);
            std::string plane, type, date, employee;
            ss >> plane >>  type >> date >> employee;
            CleaningService::ServiceType st;
            if (type=="Maintenance")
                st=CleaningService::MAINTENANCE;
            else if(type=="Cleaning")
                st=CleaningService::CLEANING;
            else
                continue;
            std::find_if(this->ownedPlanes.begin(), this->ownedPlanes.end(), [plane](const Plane& p){return p.getPlate()==plane;})->addCleaningService(CleaningService(st, date, employee));
        }
    }

}
bool Airline::addPlaneToAirlineFleet(const Plane& plane) {

    for (const auto& p : this->ownedPlanes)
        if (p == plane) return false;

    this->ownedPlanes.push_back(plane);
    ofstream planeFile("planes.txt", std::ios_base::app);
    planeFile << plane;
    this->flightPlans.push_back(FlightPlan(plane)); // adds an empty flight plan associated with this plane
    return true;
};

bool Airline::addFlightToPlane(const Plane& plane, const Flight& flight) {

    bool ret = this->addPlaneToAirlineFleet(plane); // might return false, just ensure we have the plane on the fleet

    std::find_if(this->flightPlans.begin(), this->flightPlans.end(), [plane](const FlightPlan& fp){ return fp.getPlane() == plane; })->addFlightToPlan(flight);

    return ret;
};

bool Airline::addFlightsToPlane(const Plane& plane, const std::list<Flight>& flights) {

    bool ret = this->addPlaneToAirlineFleet(plane); // might return false, just ensure we have the plane on the fleet

    auto fp = std::find_if(this->flightPlans.begin(), this->flightPlans.end(), [plane](const FlightPlan& fp){ return fp.getPlane() == plane; });

    for (const auto& flight : flights)
        fp->addFlightToPlan(flight);

    return ret;
};
