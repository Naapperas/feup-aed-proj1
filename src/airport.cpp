#include <fstream>
#include <sstream>

#include "../includes/airport.h"
#include "../includes/flight.h"

bool FlightPlan::addFlightToPlan(const Flight &f) {

    for (const auto& flight : this->plan)
        if (flight == f) return false;

    this->plan.push_back(f);
    this->plan.sort([](const Flight&a, const Flight&b){return a.getDepartureDate()<b.getDepartureDate();}); // keep flights ordered by date
    return true;
}


Airport::Airport(std::string name) : name(name), transportPlaces(LandTransportPlace(LandTransportPlace::SUBWAY, 0, "", "")) {

    std::ifstream f{name+".txt"};
    if (f.is_open())
        this->readFile(f);
    else {
        unsigned n;
        std::cout << "How many transport places do you wish to add?";
        std::cin >> n;
        readInput(n);
        writeToFile();
    }
}

void Airport::readFile(std::ifstream & f) {
    //TODO: maybe change how we store information on files ?

    while (!f.eof()) {
        std::string line;
        getline(f, line);
        stringstream ss(line);
        LandTransportPlace::TypeOfTransport tt;
        unsigned distance;
        std::string open, close, transport;
        ss >> transport >> distance >> open >> close;
        if (transport == LandTransportPlace::typePrint.at(0))
            tt = LandTransportPlace::SUBWAY;
        else if (transport == LandTransportPlace::typePrint.at(1))
            tt = LandTransportPlace::TRAIN;
        else if (transport == LandTransportPlace::typePrint.at(2))
            tt = LandTransportPlace::BUS;
        else
            continue;  // the file should only contain valid information unless it's modified externally, this will just be here to avoid any insertion error
        transportPlaces.insert(LandTransportPlace(tt, distance, open, close));
    }
}

void Airport::writeToFile() {
    //TODO: maybe change how we store information on files ?

    std::ofstream f(name+".txt");
    for(auto it = transportPlaces.begin(); it != transportPlaces.end(); it++){
        f << (*it).getTypeString() << ' ' << (*it).getDistance() << ' ' << (*it).getOpenTime() << ' ' << (*it).getCloseTime() << '\n';
    }
    f.close();
}

void Airport::readInput(unsigned int n) {
    //TODO: maybe change how we store information on files ?

    std::cin.ignore(1);
    for (int i = 0; i < n; i++) {
        std::cout << "Write here: ";
        std::string place;
        getline(cin, place);
        stringstream ss(place);
        LandTransportPlace::TypeOfTransport tt;
        unsigned distance;
        std::string open, close, transport;
        ss >> transport >> distance >> open >> close;

        // need to handle input errors here probably

        if (transport == LandTransportPlace::typePrint.at(0))
            tt = LandTransportPlace::SUBWAY;
        else if (transport == LandTransportPlace::typePrint.at(1))
            tt = LandTransportPlace::TRAIN;
        else if (transport == LandTransportPlace::typePrint.at(2))
            tt = LandTransportPlace::BUS;
        else
            continue;
        transportPlaces.insert(LandTransportPlace(tt, distance, open, close));
    }

    std::cout << std::endl;
}

void Airport::printTransportPlaces() const {

    std::cout << "Transport places near " << this->name << ": " << '\n';

    transportPlaces.printTree();

    std::cout << std::endl;
}

Ticket Airport::purchaseTicket(Flight& flight, const Passenger& passenger) {

    if (flight.getLotation() < flight.getPlane().getCapacity()) {
        Ticket t(passenger);

        return t;
    }

    throw std::string("Plane is at max capacity");
}

void Airport::landPlane(const Plane &plane) {

    if (std::find(this->landedPlanes.begin(), this->landedPlanes.end(), plane) != this->landedPlanes.end())
        throw std::string("Can't land already landed plane");

    this->landedPlanes.emplace_back(plane);
}

void Airport::planeDeparture(const Plane& plane) {

    if (std::find(this->landedPlanes.begin(), this->landedPlanes.end(), plane) == this->landedPlanes.end())
        throw std::string("Can't take off if not landed at airport");

    this->landedPlanes.remove(plane);
}

void Airport::addLuggageToTransportBelt(const Luggage& l) {
    this->luggageTransportBelt.emplace(l);
}

void Airport::loadLuggageToTransport() {
    auto &luggage = this->luggageTransportBelt.front();
    this->luggageTransportBelt.pop();

    this->transport.addLuggage(luggage);
}

void Airport::loadCargo(Plane &plane) {

    auto flightCargo = this->transport.getCargo();

    for (auto& luggage : flightCargo)
        plane.addLuggage(luggage);

}

void Airport::offloadCargo(Plane &plane) {

    //TODO: to be implemented

}


const std::vector<std::string> LandTransportPlace::typePrint = {"Subway", "Train", "Bus"};

bool operator<(const LandTransportPlace &a, const LandTransportPlace &b) {
    return (a.distance < b.distance);
}

ostream& operator <<(ostream& out , const LandTransportPlace &a) {
    out << LandTransportPlace::typePrint.at(a.type) << ' ' << a.distance << "m " << "Open from: " << a.openTime << " to " << a.closeTime;
    return out;
}