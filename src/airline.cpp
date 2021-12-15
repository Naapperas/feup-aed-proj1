//
// Created by naapperas on 13/12/21.
//
#include <algorithm>
#include <fstream>
#include <sstream>

#include "../includes/airline.h"

Airline* Airline::instance = NULL;

Airline::Airline(const std::string &name) : airlineName(name) {

    // initialize ownedPlanes
    std::ifstream planeFile{"planes.txt"};
    if (!planeFile.is_open())
        std::ofstream planeFileNew{"planes.txt"};
    else{
        while(!planeFile.eof()){
            std::string currentPlane;
            getline(planeFile,currentPlane);

            if (currentPlane.empty())
                continue;

            std::stringstream ss(currentPlane);
            std::string type, plate;
            unsigned capacity, cargoCapacity;
            ss >> type >> plate >> capacity >> cargoCapacity;
            ownedPlanes.emplace_back(type, plate, capacity, cargoCapacity);
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

            if (currentService.empty())
                continue;

            if (currentService == "[PAST CLEANING TASKS]" or currentService == "[UPCOMING CLEANING TASKS]")
                continue;

            std::stringstream ss(currentService);
            std::string planePlate, type, date, employee;
            ss >> planePlate >> type >> date >> employee;
            CleaningService::ServiceType st;
            if (type=="Maintenance")
                st=CleaningService::MAINTENANCE;
            else if(type=="Cleaning")
                st=CleaningService::CLEANING;
            else
                continue;
            std::find_if(this->ownedPlanes.begin(), this->ownedPlanes.end(), [planePlate](const Plane& p){return p.getPlate() == planePlate;})->addCleaningService(CleaningService(st, date, employee));
        }
    }
}

bool Airline::addPlaneToAirlineFleet(const Plane& plane) {

    for (const auto& p : this->ownedPlanes)
        if (p == plane) return false;

    this->ownedPlanes.push_back(plane);
    this->flightPlans.emplace_back(plane); // adds an empty flight plan associated with this plane
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

void Airline::listCurrentFlights() const {

    std::cout << "Upcoming Flights:\n\n" << std::endl;

    for (const auto& flight : this->upcomingFlights)
        std::cout << '\t' << flight.getFlightNumber() << " - Departing " << flight.getDepartureDate() << "; Duration: " << flight.getDuration() << '\n';

    std::cout << std::endl;
};

void Airline::listCurrentPlanes() const {

    std::cout << "Planes in fleet:\n" << std::endl;

    for (const auto& plane : this->ownedPlanes)
        std::cout << '\t' << plane.getType() << " Plate nº" << plane.getPlate() << "\n\t\tCapacity: " << plane.getCapacity() << '\n';

    std::cout << std::endl;
};

void Airline::purchasePlane() {

    std::string type, plate;
    unsigned capacity, cargoCapacity;

    std::cout << "What is the type/model of the new plane? >";
    std::cin >> type;

    std::cout << "What is the new plane's plate? >";
    std::cin >> plate;

    std::cout << "How many passengers can the new plane transport? >";
    std::cin >> capacity;

    std::cout << "What is the max cargo capacity of the new plane? >";
    std::cin >> cargoCapacity;

    this->addPlaneToAirlineFleet(Plane(type, plate, capacity, cargoCapacity));
}

void Airline::storePlanes() const {
    ofstream planeFile("planes.txt");

    if (planeFile.is_open())
        for (const auto& plane : this->ownedPlanes) {
            this->storeCleaningServices(plane);
            planeFile << plane;
        }
}

void Airline::storeCleaningServices(const Plane &plane) const {

    ofstream serviceFile("cleaning.txt");

    plane.storeCleaningServices(serviceFile);
}