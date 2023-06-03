cmake_minimum_required(VERSION 3.25)
project(tc1030_project_ship_A01709118)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(unit_test)

add_executable(tc1030_project_ship_A01709118
        unit_test/catch.h
        unit_test/testing_heavy.cpp
        unit_test/testing_light.cpp
        unit_test/testing_liquid.cpp
        unit_test/testing_port1.cpp
        unit_test/testing_port2.cpp
        unit_test/testing_refrigerated.cpp
        unit_test/testing_ship.cpp
        container.h
        heavy.h
        light.h
        liquid.h
        port.h
        refrigerated.h
        ship.h
        simpleship.h
        main.cpp)
