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
            this->addPlaneToAirlineFleet(new Plane(type, plate, capacity, cargoCapacity));
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
            Service::ServiceType st;
            if (type == "Maintenance")
                st = Service::MAINTENANCE;
            else if(type == "Cleaning")
                st = Service::CLEANING;
            else
                continue;
            (*std::find_if(this->ownedPlanes.begin(), this->ownedPlanes.end(),
                           [planePlate](Plane *p) { return p->getPlate() == planePlate; }))->addService(
                    Service(st, date, employee));
            // check if service was finished prior to this execution of the program and set to finish if so
            if (!upcoming)
                (*std::find_if(this->ownedPlanes.begin(), this->ownedPlanes.end(),
                               [planePlate](Plane *p) { return p->getPlate() == planePlate; }))->finishedService();
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

            auto a = new Airport{airportName};

            std::string planePlate;
            while (ss >> planePlate)
                // store current plane info
                a->landPlane(*std::find_if(this->ownedPlanes.begin(), this->ownedPlanes.end(), [planePlate](Plane* p){return p->getPlate() == planePlate;}));

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

            (*std::find_if(this->airports.begin(), this->airports.end(), [airportName](Airport* a){return a->getName() == airportName;}))->registerTransportPlace(ltp);

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

            auto plane = *std::find_if(this->ownedPlanes.begin(), this->ownedPlanes.end(), [planePlate](Plane* p){ return p->getPlate() == planePlate; });
            auto origin = *std::find_if(this->airports.begin(), this->airports.end(), [originName](Airport* a){ return a->getName() == originName; });
            auto destiny = *std::find_if(this->airports.begin(), this->airports.end(), [destinyName](Airport* a){ return a->getName() == destinyName; });

            auto f = new Flight{flightNumber, departureDate, duration, plane, origin, destiny};

            this->addFlightToPlane(plane, f);
        }
    }

    // initialize passengers
    std::ifstream passengersFile{"passengers.txt"};
    if (!passengersFile.is_open())
        std::ofstream passengersFile{"passengers.txt"};
    else {

        while (!passengersFile.eof()) {

            std::string currentFlight;
            getline(passengersFile, currentFlight);

            if (currentFlight.empty())
                continue;

            stringstream ss{currentFlight};

            int flightId;
            ss >> flightId;

            auto flight = *std::find_if(this->upcomingFlights.begin(), this->upcomingFlights.end(), [flightId](Flight* flight){ return flight->getFlightNumber() == flightId; });

            while(ss) {

                std::string passengerName, hasLuggage;
                int passengerAge;

                ss >> passengerName >> passengerAge >> hasLuggage;

                Passenger* p;

                if (hasLuggage == "Y") {
                    Luggage* l = new Luggage();
                    p = new Passenger(passengerName, passengerAge, l);
                } else if (hasLuggage == "N") {
                    p = new Passenger(passengerName, passengerAge);
                } else {
                    // misconfigured passenger, too bad for them
                    continue;
                }

                Ticket* t = new Ticket(p);

                flight->addPassenger(t);
            }
        }
    }


    for (auto& flightPlan : this->flightPlans)
        flightPlan->performFlights();

    for (auto& plane: this->ownedPlanes)
        plane->performServices();

}

bool Airline::addPlaneToAirlineFleet(Plane* plane) {

    for (const auto& p : this->ownedPlanes)
        if (p == plane) return false;

    this->ownedPlanes.push_back(plane);

    auto fp = new FlightPlan{plane};

    this->flightPlans.emplace_back(fp); // adds an empty flight plan associated with this plane
    return true;
};

bool Airline::addFlightToPlane(Plane* plane, Flight* flight) {

    bool ret = this->addPlaneToAirlineFleet(plane); // might return false, just ensure we have the plane on the fleet

    (*std::find_if(this->flightPlans.begin(), this->flightPlans.end(), [plane](FlightPlan* fp){ return fp->getPlane() == plane; }))->addFlightToPlan(flight);
    this->upcomingFlights.push_back(flight);

    return ret;
};

bool Airline::addFlightsToPlane(Plane* plane, const std::list<Flight*>& flights) {

    bool ret = this->addPlaneToAirlineFleet(plane); // might return false, just ensure we have the plane on the fleet

    auto fp = std::find_if(this->flightPlans.begin(), this->flightPlans.end(), [plane](FlightPlan* fp){ return fp->getPlane() == plane; });

    for (const auto& flight : flights)
        (*fp)->addFlightToPlan(flight);

    return ret;
};

bool Airline::cancelFlight() {

    Airline::getInstance().listCurrentFlights();

    std::cout << "\tChoose one to delete (input the flight number): ";

    long option;
    std::cin >> option;

    for (FlightPlan* fp: flightPlans) {
        if(fp->removeFlight(option)) {

            auto first = std::remove_if(upcomingFlights.begin(), upcomingFlights.end(), [option](Flight* f){return f->getFlightNumber() == option;}); // shift the flight to be removed to the end

            auto flightToDelete = upcomingFlights.back();
            delete flightToDelete;

            upcomingFlights.erase(first, upcomingFlights.end());
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

    auto flight = std::find_if(upcomingFlights.begin(), upcomingFlights.end(), [option](Flight* f){return f->getFlightNumber()==option;});

    std::cout << "\tWhat's the new departure date of this flight? The previous date is '" << (*flight)->getDepartureDate() << "' (provide input in the form YYYY-MM-DD)\n\t> ";

    std::string newDate;
    std::cin >> newDate;

    for (FlightPlan* fp: flightPlans){
        if(fp->updateFlight(option, newDate)) {
            (*flight)->setDepartureDate(newDate);
            std::sort(upcomingFlights.begin(), upcomingFlights.end(), [](Flight* a, Flight* b){return a->getDepartureDate()<b->getDepartureDate();});
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

    std::cout << "\tWhat's the departure date of this flight? (provide input in the form YYYY-MM-DD)\n\t> ";

    std::string departureDate;
    std::cin >> departureDate;

    std::cout << "\tHow long will the flight take in minutes? ";

    unsigned duration;
    std::cin >> duration;

    std::cout << '\n';

    Airline::getInstance().listAirports();

    std::cout << "\n\tWhat are the origin and destination airports ? (give input in the form {origin} {destination}) ";

    std::string origin, destination;
    std::cin >> origin >> destination;

    if (origin == destination) {
        std::cout << "\tCan't have both origin and destination be the same airport, aborting!" << std::endl;
        return;
    }

    auto originAirport = *std::find_if(this->airports.begin(), this->airports.end(), [origin](Airport* a){ return a->getName() == origin; });
    auto destinyAirport = *std::find_if(this->airports.begin(), this->airports.end(), [destination](Airport* a){ return a->getName() == destination; });

    auto& plane = *std::find_if(this->ownedPlanes.begin(), this->ownedPlanes.end(), [planePlate](Plane* p){ return p->getPlate() == planePlate; });

    auto f = new Flight{departureDate, duration, plane, originAirport, destinyAirport};

    this->addFlightToPlane(plane, f);
}

void Airline::listCurrentFlights() const {

    std::cout << "\tUpcoming Flights:\n" << std::endl;

    for (auto flight : this->getValidFlights())
        std::cout << '\t' << flight->getFlightNumber() << " - Departing " << flight->getDepartureDate() << " from " << flight->getOriginAirport()->getName() << " to " << flight->getDestinationAirport()->getName() << "; Duration: " << flight->getDuration() << " minutes\n\t\t" << "Current: flight lotation: " << flight->getLotation() << '\n';

    std::cout << std::endl;
};

void Airline::listCurrentPlanes(bool verbose) const {

    std::cout << "\n\tPlanes in fleet:\n" << std::endl;

    for (auto plane : this->ownedPlanes) {
        std::cout << "\t\t" << plane->getType() << " Plate nº" << plane->getPlate();
        if (verbose)
            std::cout << "\n\t\t\tCapacity: " << plane->getCapacity() << '\n';
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

    this->addPlaneToAirlineFleet(new Plane(type, plate, capacity, cargoCapacity));
}

void Airline::listAirports() const {

    unsigned counter = 1;

    for (const auto& airport : this->airports)
        std::cout << "\t[" << counter++ << "] " << airport->getName() << '\n';
}

bool Airline::addAirport(Airport* airport) {
    for (auto a : this->airports)
        if (a == airport) return false;

    this->airports.push_back(airport);
    return true;
}

void Airline::registerAirport(){
    std::string name;
    std::cout << "\tWhat is the name of the airport to be registered? \n\t>";
    std::cin >> name;

    this->addAirport(new Airport(name));
}

void Airline::registerTransportPlace() {

    Airport* a;

    if (this->airports.size() == 1) {
        std::cout << "\tSelecting only airport registered\n";
        a = this->airports.at(0);
    }
    else {

        this->listAirports();

        unsigned option;

        std::cout << "\n\tWhich is the closest airport to the new transport place?\n\t> ";
        std::cin >> option;

        a = (*(this->airports.begin() + option-1));
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

void Airline::updateTransportPlace() {
    Airport* a;

    if (this->airports.size() == 1) {
        std::cout << "\tSelecting only airport registered\n";
        a = this->airports.at(0);
    }
    else {

        this->listAirports();

        unsigned option;

        std::cout << "\n\tWhich is the closest airport to this transport place?\n\t> ";
        std::cin >> option;

        a = (*(this->airports.begin() + option-1));
    }

    std::string type, openTime, closeTime;
    unsigned distance;
    a->printTransportPlaces();

    std::cout << "\tWhich is the type of transport? (can be one of Train, Bus or Subway)\n\t> ";
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

    std::cout << "\tWhat is the new schedule of this transport?\n\t\tPlease input the values in the form {openTime} {closeTime}, with each having the form HH:MM\n\t> ";
    std::cin >> openTime >> closeTime;

    LandTransportPlace ltp{tt, distance, openTime, closeTime};

    if(!a->updateTransportPlace(ltp))
        std::cout << "\tThis transport place can't be updated, as it doesn't exist, aborting operation" << std::endl;
}

void Airline::storePlanes() const {
    ofstream planeFile("planes.txt");

    // reset cleaning service's file
    ofstream serviceFile("cleaning.txt");
    serviceFile << "";

    if (planeFile.is_open())
        for (auto plane : this->ownedPlanes) {
            this->storeCleaningServices(plane);
            planeFile << *plane;
        }
}

void Airline::storeCleaningServices(Plane *plane) const {

    ofstream serviceFile("cleaning.txt", std::ios_base::app);

    plane->storeCleaningServices(serviceFile);
}

void Airline::storeAirports() const {

    ofstream planeFile("airports.txt");

    // reset cleaning service's file
    ofstream transportPlaces("transportPlaces.txt");
    transportPlaces << "";

    if (planeFile.is_open())
        for (auto airport : this->airports) {
            this->storeTransportPlaces(airport);
            planeFile << *airport;
        }
}

void Airline::storeTransportPlaces(Airport *airport) const {

    ofstream transportPlacesFile("transportPlaces.txt", std::ios_base::app);

    airport->storeTransportPlaces(transportPlacesFile);
}

void Airline::storeFlights() const {

    ofstream flightsFile("flights.txt");

    ofstream passengersFile("passengers.txt");
    passengersFile << "";

    if (flightsFile.is_open())
        for (auto flight : this->getValidFlights()) {
            this->storePassengers(flight);
            flightsFile << *flight;
        }
}

void Airline::purchaseTicket() {

    this->listCurrentFlights();

    long option;
    std::cout << "\tPlease select the number of the flight you wish to take\n\t> ";
    std::cin >> option;

    auto itr = std::find_if(this->upcomingFlights.begin(), this->upcomingFlights.end(), [option](const Flight* flight){return flight->getFlightNumber() == option;});

    std::cout << "\tHow many passengers will be coming aboard\n\t> ";
    std::cin >> option;

    std::vector<Ticket*> tickets;
    for (unsigned i = 0; i < option; i++){
        std::string name;
        std::cout << "\tPlease insert the name of the passenger\n\t> ";
        std::cin >> name;

        unsigned age;
        std::cout << "\tPlease insert the age of the passenger\n\t> ";
        std::cin >> age;

        char carryLuggage;
        std::cout << "\tWill they be carrying luggage? Y/N\n\t> ";
        std::cin >> carryLuggage;

        if (toupper(carryLuggage) == 'Y') {
            auto luggage = new Luggage();
            auto passenger = new Passenger(name, age, luggage);
            auto ticket = new Ticket(passenger);

            tickets.push_back(ticket);
        } else {
            auto passenger = new Passenger(name, age);
            auto ticket = new Ticket(passenger);

            tickets.push_back(ticket);
        }
    }

    if (tickets.size() != 1)
        (*itr)->addPassengers(tickets);
    else
        (*itr)->addPassenger(tickets[0]);

    std::cout << "\tWe successfully entered the data. Have a safe flight" << std::endl;
}

void Airline::listTransportPlaces() const{
    Airport* a;

    if (this->airports.size() == 1) {
        std::cout << "\tSelecting only airport registered\n";
        a = this->airports.at(0);
    }
    else {

        this->listAirports();

        unsigned option;

        std::cout << "\n\tWhich airport's nearby transports would you like to see?\n\t> ";
        std::cin >> option;

        a = (*(this->airports.begin() + option-1));
    }

    a->printTransportPlaces();
}

std::vector<Flight*> Airline::getValidFlights() const {

    std::vector<Flight*> tmp;

    for (auto flight : this->upcomingFlights)
        if (!FlightPlan::isPast(flight->getDepartureDate()))
            tmp.push_back(flight);

    return tmp;
}

void Airline::addCleaningService() {

    this->listCurrentPlanes();

    std::string option;
    std::cout << "\tPlease select the plate of the plane you wish to add the service\n\t> ";
    std::cin >> option;

    auto itr = std::find_if(this->ownedPlanes.begin(), this->ownedPlanes.end(), [option](Plane* plane){ return plane->getPlate() == option; });

    Service::ServiceType st;
    std::cout << "\tWhat's the type of the service. M/C\n\t> "; // M = MAINTENANCE / C = CLEANING
    std::cin >> option;

    if (toupper(option[0]) == 'M')
        st = Service::MAINTENANCE;
    else if (toupper(option[0]) == 'C')
        st = Service::CLEANING;
    else {
        std::cout << "\tInvalid service type, aborting operation" << std::endl;
        return;
    }

    std::string date;
    std::cout << "\tWhat's the date of the service. YYYY-MM-DD\n\t> ";
    std::cin >> date;

    std::cout << "\tWhat's the name of the employee?\n\t> ";
    std::cin >> option;

    if (!(*itr)->addService(Service(st, date, option))){
        std::cout << "\tUnable to add a service on this date, aborting operation" << std::endl;
    }
}

void Airline::storePassengers(Flight* flight) const {

    if (flight->getPassengers().size() == 0)
        return;

    ofstream passengersFile("passengers.txt", std::ios_base::app);

    if (passengersFile.is_open()) {
        passengersFile << flight->getFlightNumber() << ' ';
        for (auto passenger : flight->getPassengers())
            passengersFile << passenger->getPassenger()->getName() << ' ' << passenger->getPassenger()->getAge() << ' ' << (passenger->getPassenger()->hasLuggage() ? "Y" : "N") << ' ';

        passengersFile << '\n';
    }
}