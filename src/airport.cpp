#include "../includes/airport.h"

Airport::Airport(std::string name):name(name), transportPlaces(LandTransportPlace(LandTransportPlace::SUBWAY, 0, "", "")) {
    ifstream transportPlacesFile(name + ".txt");
    readFile(transportPlacesFile);
}

void Airport::readFile(ifstream & f){
    while (!f.eof()){
        std::string line;
        getline(cin, line);
        stringstream ss(line);
        LandTransportPlace::TypeOfTransport tt;
        unsigned distance;
        std::string open, close, transport;
        ss >> transport >> distance >> open >> close;
        // hopefully just a temporary solution
        if (transport == "SUBWAY")
            tt = LandTransportPlace::SUBWAY;
        else if (transport == "TRAIN")
            tt = LandTransportPlace::TRAIN;
        else
            tt = LandTransportPlace::BUS;
        transportPlaces.insert(LandTransportPlace(tt, distance, open, close));
    }
}