cmake_minimum_required(VERSION 4.1)
project(Flight_Computer)

set(CMAKE_CXX_STANDARD 20)

add_executable(Flight_Computer src/main.cpp
        src/Scheduler/Scheduler.h
        src/Scheduler/Scheduler.cpp
        src/FlightLoop/FlightLoop.h
        src/FlightLoop/FlightLoop.cpp
        src/Sensors/GyroSensor.cpp
        src/Sensors/GyroSensor.h
        src/Control/Controller.cpp
        src/Control/Controller.h
        src/Logging/Logger.cpp
        src/Logging/Logger.h
        src/Sensors/Dynamics/RigidBody1D.cpp
        src/Sensors/Dynamics/RigidBody1D.h)
