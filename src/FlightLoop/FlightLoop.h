#pragma once

#include <cstdint>
#include "../Sensors/Dynamics/RigidBody1D.h"
#include "../Sensors/GyroSensor.h"

class FlightLoop {
public:
    FlightLoop();
    void tick();

private:
    std::uint64_t m_tickCounter = 0;
    RigidBody1D m_body;
    GyroSensor m_gyro;
};
