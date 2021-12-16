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
            this->addPlaneToAirlineFleet(Plane(type, plate, capacity, cargoCapacity));
        }
    }

    // initialize cleaning services for owned planes
    std::ifstream serviceFile{"cleaning.txt"};
    if (!planeFile.is_open())
        std::ofstream serviceFileNew{"cleaning.txt"};
    else{
        bool upcoming = false;
        while(!serviceFile.eof()){
            std::string currentService;
            getline(serviceFile,currentService);

            if (currentService.empty())
                continue;

            if (currentService == "[PAST CLEANING TASKS]") {
                upcoming = false;
                continue;
            }

            if (currentService == "[UPCOMING CLEANING TASKS]"){
                upcoming = true;
                continue;
            }

            std::stringstream ss(currentService);
            std::string planePlate, type, date, employee;
            ss >> planePlate >> type >> date >> employee;
            CleaningService::ServiceType st;
            if (type == "Maintenance")
                st = CleaningService::MAINTENANCE;
            else if(type == "Cleaning")
                st = CleaningService::CLEANING;
            else
                continue;
            std::find_if(this->ownedPlanes.begin(), this->ownedPlanes.end(), [planePlate](const Plane& p){return p.getPlate() == planePlate;})->addCleaningService(CleaningService(st, date, employee));
            // check if service was finished prior to this execution of the program and set to finish if so
            if (!upcoming)
                std::find_if(this->ownedPlanes.begin(), this->ownedPlanes.end(), [planePlate](const Plane& p){return p.getPlate() == planePlate;})->finishedCleaningService();
        }
    }

    // initialize airports
    std::ifstream airportsFile{"airports.txt"};
    if (!planeFile.is_open())
        std::ofstream serviceFileNew{"airports.txt"};
    else {
        while (!airportsFile.eof()) {

            std::string currentAirport;
            getline(airportsFile, currentAirport);

            if (currentAirport.empty())
                continue;

            stringstream ss{currentAirport};
            std::string airportName;

            ss >> airportName;

            Airport a{airportName};

            std::string planePlate;
            while (ss >> planePlate)
                // store current plane info
                a.landPlane(*std::find_if(this->ownedPlanes.begin(), this->ownedPlanes.end(), [planePlate](const Plane& p){return p.getPlate() == planePlate;}));

            this->airports.push_back(a);
        }
    }

    // initialize transportPlaces
    std::ifstream landTransportsFile{"transportPlaces.txt"};
    if (!planeFile.is_open())
        std::ofstream landTransportsFileNew{"transportPlaces.txt"};
    else {
        while (!landTransportsFile.eof()) {

            std::string currentTransportPlace;
            getline(landTransportsFile, currentTransportPlace);

            if (currentTransportPlace.empty())
                continue;

            stringstream ss{currentTransportPlace};
            std::string airportName, openTime, closeTime;
            unsigned typeNumber, distance;

            ss >> airportName >> typeNumber >> distance >> openTime >> closeTime;

            LandTransportPlace::TypeOfTransport type = LandTransportPlace::getTypeOfTransport(typeNumber);

            LandTransportPlace ltp{type, distance, openTime, closeTime};

            std::find_if(this->airports.begin(), this->airports.end(), [airportName](const Airport& a){return a.getName() == airportName;})->registerTransportPlace(ltp);

        }
    }

    // initialize flights
    std::ifstream flightsFile{"flights.txt"};
    if (!planeFile.is_open())
        std::ofstream flightsNew{"flights.txt"};
    else {

        while (!flightsFile.eof()) {

            std::string currentFlight;
            getline(flightsFile, currentFlight);

            if (currentFlight.empty())
                continue;

            stringstream ss{currentFlight};
            std::string departureDate, planePlate, originName, destinyName;
            long flightNumber;
            unsigned duration;

            ss >> flightNumber >> departureDate >> duration >> planePlate >> originName >> destinyName;

            auto& plane = *std::find_if(this->ownedPlanes.begin(), this->ownedPlanes.end(), [planePlate](const Plane& p){ return p.getPlate() == planePlate; });
            auto& origin = *std::find_if(this->airports.begin(), this->airports.end(), [originName](const Airport& a){ return a.getName() == originName; });
            auto& destiny = *std::find_if(this->airports.begin(), this->airports.end(), [destinyName](const Airport& a){ return a.getName() == destinyName; });

            Flight f{flightNumber, departureDate, duration, plane, origin, destiny};

            this->addFlightToPlane(plane, f);
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
    this->upcomingFlights.push_back(flight);

    return ret;
};

bool Airline::addFlightsToPlane(const Plane& plane, const std::list<Flight>& flights) {

    bool ret = this->addPlaneToAirlineFleet(plane); // might return false, just ensure we have the plane on the fleet

    auto fp = std::find_if(this->flightPlans.begin(), this->flightPlans.end(), [plane](const FlightPlan& fp){ return fp.getPlane() == plane; });

    for (const auto& flight : flights)
        fp->addFlightToPlan(flight);

    return ret;
};

bool Airline::cancelFlight() {

    Airline::getInstance().listCurrentFlights();

    std::cout << "\tChoose one to delete (input the flight number): ";

    long option;
    std::cin >> option;

    for (FlightPlan& fp: flightPlans){
        if(fp.removeFlight(option)) {
            upcomingFlights.erase(std::remove_if(upcomingFlights.begin(), upcomingFlights.end(), [option](const Flight& f){return f.getFlightNumber() == option;}), upcomingFlights.end());
            std::cout << "\tFlight nº" << option << " canceled" << std::endl;
            return true;
        }
    }
    return false;
}

bool Airline::rescheduleFlight() {

    Airline::getInstance().listCurrentFlights();

    std::cout << "\tChoose one to reschedule (input the flight number): ";

    long option;
    std::cin >> option;

    std::cout << "\tWhat's the new departure date of this flight? (provide input in the form YYYY-MM-DD)";

    std::string newDate;
    std::cin >> newDate;

    for (FlightPlan& fp: flightPlans){
        if(fp.updateFlight(option, newDate)) {
            std::find_if(upcomingFlights.begin(), upcomingFlights.end(), [option](const Flight& f){return f.getFlightNumber()==option;})->setDepartureDate(newDate);
            std::sort(upcomingFlights.begin(), upcomingFlights.end(), [](const Flight&a, const Flight&b){return a.getDepartureDate()<b.getDepartureDate();});
            std::cout << "\tFlight nº" << option << " rescheduled to " << newDate << std::endl;
            return true;
        }
    }
    return false;
}

void Airline::createFlight() {

    Airline::getInstance().listCurrentPlanes();

    std::cout << "\tChoose a plane to perform the flight (write the plate): ";

    std::string planePlate;
    std::cin >> planePlate;

    std::cout << "\tWhat's the departure date of this flight? (provide input in the form YYYY-MM-DD)";

    std::string departureDate;
    std::cin >> departureDate;

    std::cout << "\tHow long will the flight take?";

    unsigned duration;
    std::cin >> duration;

    std::cout << '\n';

    Airline::getInstance().listAirports();

    std::cout << "\n\tWhat are the origin and destination airports ? (give input in the form {origin} {destination}) ";

    std::string origin, destination;
    std::cin >> origin >> destination;

    auto& originAirport = *std::find_if(this->airports.begin(), this->airports.end(), [origin](const Airport& a){ return a.getName() == origin; });
    auto& destinyAirport = *std::find_if(this->airports.begin(), this->airports.end(), [destination](const Airport& a){ return a.getName() == destination; });

    auto& plane = *std::find_if(this->ownedPlanes.begin(), this->ownedPlanes.end(), [planePlate](const Plane& p){ return p.getPlate() == planePlate; });

    Flight f{departureDate, duration, plane, originAirport, destinyAirport};

    this->addFlightToPlane(plane, f);

}

void Airline::listCurrentFlights() const {

    std::cout << "\tUpcoming Flights:\n" << std::endl;

    for (const auto& flight : this->upcomingFlights)
        std::cout << '\t' << flight.getFlightNumber() << " - Departing " << flight.getDepartureDate() << "; Duration: " << flight.getDuration() << "\n\t\t" << "Current: flight lotation: " << flight.getLotation() << '\n';

    std::cout << std::endl;
};

void Airline::listCurrentPlanes(bool verbose) const {

    std::cout << "\n\tPlanes in fleet:\n" << std::endl;

    for (const auto& plane : this->ownedPlanes) {
        std::cout << "\t\t" << plane.getType() << " Plate nº" << plane.getPlate();
        if (verbose)
            std::cout << "\n\t\t\tCapacity: " << plane.getCapacity() << '\n';
    }

    std::cout << std::endl;
};

void Airline::purchasePlane() {

    std::string type, plate;
    unsigned capacity, cargoCapacity;

    std::cout << "\tWhat is the type/model of the new plane? >";
    std::cin >> type;

    std::cout << "\tWhat is the new plane's plate? >";
    std::cin >> plate;

    std::cout << "\tHow many passengers can the new plane transport? >";
    std::cin >> capacity;

    std::cout << "\tWhat is the max cargo capacity of the new plane? >";
    std::cin >> cargoCapacity;

    this->addPlaneToAirlineFleet(Plane(type, plate, capacity, cargoCapacity));
}

void Airline::listAirports() const {

    unsigned counter = 1;

    for (const auto& airport : this->airports)
        std::cout << "\t[" << counter++ << "] " << airport.getName() << '\n';
}

bool Airline::addAirport(const Airport &airport) {
    for (const auto& a : this->airports)
        if (a == airport) return false;

    this->airports.push_back(airport);
    return true;
}

void Airline::registerAirport(){
    std::string name;
    std::cout << "\tWhat is the name of the airport to be registered? \n\t>";
    std::cin >> name;

    this->addAirport(Airport(name));
}

void Airline::registerTransportPlace() {

    Airport* a;

    if (this->airports.size() == 1) {
        std::cout << "\tSelecting only airport registered\n";
        a = &this->airports.at(0);
    }
    else {

        this->listAirports();

        unsigned option;

        std::cout << "\n\tWhich is the closest airport to the new transport place?\n\t> ";
        std::cin >> option;

        a = &(*(this->airports.begin() + option-1));
    }

    std::string type, openTime, closeTime;
    unsigned distance;

    std::cout << "\tWhat is the type of the new transport? (can be one of Train, Bus or Subway)\n\t> ";
    std::cin >> type;

    LandTransportPlace::TypeOfTransport tt;

    if (type == LandTransportPlace::typePrint.at(0))
        tt = LandTransportPlace::SUBWAY;
    else if (type == LandTransportPlace::typePrint.at(1))
        tt = LandTransportPlace::TRAIN;
    else if (type == LandTransportPlace::typePrint.at(2))
        tt = LandTransportPlace::BUS;
    else {
        std::cout << "\tInvalid transport type, aborting operation" << std::endl;
        return;
    }

    std::cout << "\tHow far is it from the airport? (distance in meters)\n\t> ";
    std::cin >> distance;

    std::cout << "\tWhat is the schedule of this new transport?\n\t\tPlease input the values in the form {openTime} {closeTime}, with each havin the form HH:MM\n\t> ";
    std::cin >> openTime >> closeTime;

    LandTransportPlace ltp{tt, distance, openTime, closeTime};

    a->registerTransportPlace(ltp);
}

void Airline::storePlanes() const {
    ofstream planeFile("planes.txt");

    // reset cleaning service's file
    ofstream serviceFile("cleaning.txt");
    serviceFile << "";

    if (planeFile.is_open())
        for (const auto& plane : this->ownedPlanes) {
            this->storeCleaningServices(plane);
            planeFile << plane;
        }
}

void Airline::storeCleaningServices(const Plane &plane) const {

    ofstream serviceFile("cleaning.txt", std::ios_base::app);

    plane.storeCleaningServices(serviceFile);
}

void Airline::storeAirports() const {

    ofstream planeFile("airports.txt");

    // reset cleaning service's file
    ofstream transportPlaces("transportPlaces.txt");
    transportPlaces << "";

    if (planeFile.is_open())
        for (const auto& airport : this->airports) {
            this->storeTransportPlaces(airport);
            planeFile << airport;
        }
}

void Airline::storeTransportPlaces(const Airport &airport) const {

    ofstream transportPlacesFile("transportPlaces.txt", std::ios_base::app);

    airport.storeTransportPlaces(transportPlacesFile);
}

void Airline::storeFlights() const {

    ofstream flightsFile("flights.txt");

    if (flightsFile.is_open())
        for (Flight flight : this->upcomingFlights)
            flightsFile << flight;
}

void Airline::purchaseTicket() {
    long option;
    std::cout << "\tPlease select the number of the flight you wish to take\n\t> ";
    std::cin >> option;

    auto itr = std::find_if(this->upcomingFlights.begin(), this->upcomingFlights.end(), [option](const Flight& flight){return flight.getFlightNumber() == option;});

    std::cout << "\tHow many passengers will be coming aboard\n\t> ";
    std::cin >> option;

    std::vector<Ticket> tickets;
    for (unsigned i = 0; i < option; i++){
        std::string name;
        std::cout << "\tPlease insert the name of the passenger\n\t> ";
        std::cin >> name;

        unsigned age;
        std::cout << "\tPlease insert the age of the passenger\n\t> ";
        std::cin >> age;

        char carryLuggage;
        std::cout << "\tWill he/her be carrying luggage? Y or N\n\t> ";
        std::cin >> carryLuggage;

        if (toupper(carryLuggage) == 'Y'){
            Luggage luggage;
            Passenger passenger(name, age, luggage);
            Ticket ticket(passenger);

            tickets.push_back(ticket);
        }
        else{
            Passenger passenger(name, age);
            Ticket ticket(passenger);

            tickets.push_back(ticket);
        }
    }

    if (tickets.size() != 1)
        itr->addPassengers(tickets);
    else
        itr->addPassenger(tickets[0]);

    std::cout << "\tWe successfully entered the data. Have a safe flight" << std::endl;
}
