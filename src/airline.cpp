//
// Created by naapperas on 13/12/21.
//
#include <algorithm>

#include "../includes/airline.h"

bool Airline::addPlaneToAirlineFleet(const Plane& plane) {

    for (const auto& p : this->ownedPlanes)
        if (p == plane) return false;

    this->ownedPlanes.push_back(plane);
    this->flightPlans.push_back(FlightPlan(plane)); // adds an empty flight plan associated with this plane
    return true;
};

bool Airline::addFlightToPlane(const Plane& plane, const Flight& flight) {

    this->addPlaneToAirlineFleet(plane); // might return false, just ensure we have the plane on the fleet

    std::find_if(this->flightPlans.begin(), this->flightPlans.end(), [plane](const FlightPlan& fp){ return fp.getPlane() == plane; })->addFlightToPlan(flight);
};

bool Airline::addFlightsToPlane(const Plane& plane, const std::list<Flight>& flights) {

    this->addPlaneToAirlineFleet(plane); // might return false, just ensure we have the plane on the fleet

    auto fp = std::find_if(this->flightPlans.begin(), this->flightPlans.end(), [plane](const FlightPlan& fp){ return fp.getPlane() == plane; });

    for (const auto& flight : flights)
        fp->addFlightToPlan(flight);
};
