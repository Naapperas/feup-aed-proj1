#include <fstream>
#include <sstream>

#include "../includes/airport.h"
#include "../includes/flight.h"

bool FlightPlan::addFlightToPlan(Flight *f) {

    for (const auto& flight : this->plan)
        if (flight == f) return false;

    this->plan.push_back(f);
    this->plan.sort([](Flight* a, Flight* b){return a->getDepartureDate()<b->getDepartureDate();}); // keep flights ordered by date
    return true;
}

bool FlightPlan::removeFlight(long flightNumber) {
    for (auto it = plan.begin(); it != plan.end(); it++){
        if ((*it)->getFlightNumber() == flightNumber) {
            plan.erase(it);
            return true;
        }
    }
    return false;
}

bool FlightPlan::updateFlight(long flightNumber, std::string newDate) {
    for (auto f : plan){
        if (f->getFlightNumber() == flightNumber){
            f->setDepartureDate(newDate);
            this->plan.sort([](const Flight* a, const Flight* b){return a->getDepartureDate()<b->getDepartureDate();}); // keep flights ordered by date
            return true;
        }
    }
    return false;
}


void Airport::printTransportPlaces() const {

    std::cout << "Transport places near " << this->name << ": " << '\n';

    transportPlaces.printTree();

    std::cout << std::endl;
}

void Airport::landPlane(Plane *plane) {

    if (std::find(this->landedPlanes.begin(), this->landedPlanes.end(), plane) != this->landedPlanes.end())
        throw std::string("Can't land already landed plane");

    this->landedPlanes.emplace_back(plane);
}

void Airport::planeDeparture(Plane *plane) {

    if (std::find(this->landedPlanes.begin(), this->landedPlanes.end(), plane) == this->landedPlanes.end())
        throw std::string("Can't take off if not landed at airport");

    this->landedPlanes.remove(plane);
}

bool Airport::planeIsLanded(Plane *plane) {
    if (std::find(this->landedPlanes.begin(), this->landedPlanes.end(), plane) != this->landedPlanes.end())
        return true;
    return false;
}

void Airport::addLuggageToTransportBelt(Luggage* l) {
    this->luggageTransportBelt.emplace(l);
}

void Airport::loadLuggageToTransport() {
    auto luggage = this->luggageTransportBelt.front();
    this->luggageTransportBelt.pop();

    this->transport.addLuggage(luggage);
}

void Airport::loadCargo(Plane *plane) {

    auto flightCargo = this->transport.getCargo();

    for (auto& luggage : flightCargo)
        plane->addLuggage(luggage);

}

void Airport::offloadCargo(Plane *plane) {
    plane->offLoadCargo();
}

void Airport::storeTransportPlaces(ofstream &file) const {

    for (auto itr = this->transportPlaces.begin(); itr != this->transportPlaces.end(); itr++) {

        auto transportPlace = *itr;

        file << this->getName() << ' ' << transportPlace.getType() << ' ' << transportPlace.getDistance() << ' ' << transportPlace.getOpenTime() << ' ' << transportPlace.getCloseTime() << '\n';
    }
}

void Airport::registerTransportPlace(const LandTransportPlace &ltp) {
    this->transportPlaces.insert(ltp);
}

bool Airport::updateTransportPlace(const LandTransportPlace &ltp) {
    iteratorBST<LandTransportPlace> it1;
    for (auto it = transportPlaces.begin(); it!=transportPlaces.end(); it++) {
        it1=it;
        if ((*it).getType() == ltp.getType() && (*it).getDistance() == ltp.getDistance())
            break;
    }
    it1++;
    if (it1==transportPlaces.end())
        return false;
    this->transportPlaces.remove(this->transportPlaces.find((*it1)));
    this->transportPlaces.insert(ltp);
    return true;
}

const std::vector<std::string> LandTransportPlace::typePrint = {"Subway", "Train", "Bus"};

bool operator<(const LandTransportPlace &a, const LandTransportPlace &b) {
    return (a.distance < b.distance);
}

ostream& operator <<(ostream& out , const LandTransportPlace &a) {
    out << LandTransportPlace::typePrint.at(a.type) << ' ' << a.distance << "m " << "Open from: " << a.openTime << " to " << a.closeTime;
    return out;
}

void FlightPlan::performFlights() {

    auto flight = this->plan.begin();

    while (flight != this->plan.end()) {

        // execute past flights
        if (isPast((*flight)->getDepartureDate())) {
            (*flight)->execute();

            flight = this->plan.erase(flight);
        } else
            flight++;
    }
}