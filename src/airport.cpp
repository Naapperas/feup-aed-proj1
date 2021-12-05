#include "../includes/airport.h"

std::vector<std::string> typePrint = {"Subway", "Train", "Bus"};

Airport::Airport(std::string name):name(name), transportPlaces(LandTransportPlace(LandTransportPlace::SUBWAY, 0, "", "")) {
    unsigned n;
    std::cout << "How many transport places do you wish to add?";
    std::cin >> n;
    readInput(n);
    writeToFile();
}

Airport::Airport(std::string name, std::ifstream&f):name(name), transportPlaces(LandTransportPlace(LandTransportPlace::SUBWAY, 0, "", "")) {
    readFile(f);
}

void Airport::readFile(std::ifstream & f){
    while (!f.eof()){
        std::string line;
        getline(cin, line);
        stringstream ss(line);
        LandTransportPlace::TypeOfTransport tt;
        unsigned distance;
        std::string open, close, transport;
        ss >> transport >> distance >> open >> close;
        if (transport == "Subway")
            tt = LandTransportPlace::SUBWAY;
        else if (transport == "Train")
            tt = LandTransportPlace::TRAIN;
        else
            tt = LandTransportPlace::BUS;
        transportPlaces.insert(LandTransportPlace(tt, distance, open, close));
    }
}

void Airport::writeToFile() {
    std::ofstream f(name+".txt");
    // do things I guess
    f.close();
}

void Airport::readInput(unsigned int n) {
    for (int i = 0; i < n; i++) {
        std::string place;
        getline(cin, place);
        stringstream ss(place);
        LandTransportPlace::TypeOfTransport tt;
        unsigned distance;
        std::string open, close, transport;
        ss >> transport >> distance >> open >> close;
        if (transport == "Subway")
            tt = LandTransportPlace::SUBWAY;
        else if (transport == "Train")
            tt = LandTransportPlace::TRAIN;
        else
            tt = LandTransportPlace::BUS;
        transportPlaces.insert(LandTransportPlace(tt, distance, open, close));
    }
}

void Airport::printTransportPlaces() {
    transportPlaces.printTree();
}