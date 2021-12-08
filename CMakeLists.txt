cmake_minimum_required(VERSION 3.20)
project(AED2122PROJ)

set(CMAKE_CXX_STANDARD 23)

add_executable(project main.cpp includes/flight.h includes/plane.h includes/passenger.h includes/luggage.h includes/airport.h includes/bst.h src/plane.cpp src/airport.cpp src/flight.cpp includes/ticket.h src/passenger.cpp src/ticket.cpp includes/luggageTransport.h includes/carriage.h)
