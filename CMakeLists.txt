cmake_minimum_required(VERSION 3.16)

project(PreliminarySizing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_executable(PreliminarySizing
    src/main.cpp
    src/gui/MainWindow.cpp
    include/sizing/gui/MainWindow.h
    src/AircraftClass.cpp
    src/WeightEstimator.cpp
    src/Mission.cpp
    src/segments/TaxiTakeoffSegment.cpp
    src/segments/ClimbSegment.cpp
    src/segments/CruiseRangeSegment.cpp
    src/segments/JetCruiseRangeSegment.cpp
    src/segments/PropellerCruiseRangeSegment.cpp
    src/segments/DescentSegment.cpp
    src/segments/ReserveCruiseSegment.cpp
    src/segments/JetReserveCruiseSegment.cpp
    src/segments/PropellerReserveCruiseSegment.cpp
    src/segments/LandingSegment.cpp

    resources.qrc
)

target_include_directories(PreliminarySizing PRIVATE include)

target_link_libraries(PreliminarySizing PRIVATE Qt6::Widgets)