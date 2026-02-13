#include "FlightLoop.h"
#include <iostream>

// Constants for simulation
static constexpr double dt = 0.01; // 10 ms (scheduler frequency = 100 Hz)

// Target attitude (setpoint)
static constexpr double TARGET_ANGLE = 0.5; // rad (target attitude)

// PID Controller gains (systematic PD tuning for attitude control)
// Ki disabled for pure derivative action feedback
static constexpr double Kp = 0.6;
static constexpr double Ki = 0.0;
static constexpr double Kd = 0.4;
static constexpr double OUTPUT_LIMIT = 0.1; // Max torque (N·m)

FlightLoop::FlightLoop()
    : m_tickCounter(0),
      m_body(1.0), // moment of inertia = 1.0
      m_gyro(m_body),
      m_controller(Kp, Ki, Kd, OUTPUT_LIMIT)
{
}

void FlightLoop::tick() {
    // 1) Increment tick counter
    m_tickCounter++;

    // 2) Read current attitude (angle) from body
    double angle = m_body.getAngle();

    // 3) Compute required torque using PID (setpoint = TARGET_ANGLE)
    double torque = m_controller.compute(TARGET_ANGLE, angle, dt);

    // 4) Apply torque to body
    m_body.setTorque(torque);

    // 5) Update dynamics (integrates velocity and angle)
    m_body.update(dt);

    // 6) Read angular velocity for logging
    double omega = m_gyro.readAngularVelocity();

    // 7) Log every 100 ticks
    if (m_tickCounter % 100 == 0) {
        std::cout << "Tick: " << m_tickCounter << " | θ = " << angle << " rad | ω = " << omega << " rad/s | τ = " << torque << " N·m\n";
    }
}
