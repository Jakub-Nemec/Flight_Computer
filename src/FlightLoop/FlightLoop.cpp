#include "FlightLoop.h"
#include <iostream>

// Constants for simulation
static constexpr double dt = 0.01; // 10 ms (scheduler frequency = 100 Hz)
static constexpr double TORQUE = 0.001; // N·m (test value)

FlightLoop::FlightLoop()
    : m_tickCounter(0),
      m_body(1.0), // moment of inertia = 1.0
      m_gyro(m_body)
{
}

void FlightLoop::tick() {
    // 1) Increment tick counter
    m_tickCounter++;

    // 2) Set torque (constant test value)
    m_body.setTorque(TORQUE);

    // 3) Update dynamics
    m_body.update(dt);

    // 4) Read angular velocity from gyro
    double omega = m_gyro.readAngularVelocity();

    // 5) Log every 100 ticks
    if (m_tickCounter % 100 == 0) {
        std::cout << "Tick: " << m_tickCounter << " | Angular velocity: " << omega << " rad/s\n";
    }
}
