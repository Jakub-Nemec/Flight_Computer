#include "PIDController.h"
#include <algorithm>

PIDController::PIDController(double kp, double ki, double kd, double outputLimit)
    : m_kp(kp), m_ki(ki), m_kd(kd), m_outputLimit(outputLimit)
{
}

double PIDController::compute(double setpoint, double measurement, double dt) {
    // 1) Calculate error
    double error = setpoint - measurement;

    // 2) Calculate derivative (handle first run to avoid spike)
    double derivative = 0.0;
    if (!m_firstRun) {
        derivative = (error - m_previousError) / dt;
    }
    m_firstRun = false;

    // 3) Compute PID output (without clamping yet)
    double output = m_kp * error + m_ki * m_integral + m_kd * derivative;

    // 4) Anti-windup: Only integrate if output is not saturated
    // This prevents integral windup when actuator is at limits
    if (output > -m_outputLimit && output < m_outputLimit) {
        // Not saturated - integrate normally
        m_integral += error * dt;
    } else {
        // Saturated - only let integral reduce error
        if ((output > 0 && error < 0) || (output < 0 && error > 0)) {
            m_integral += error * dt;
        }
    }

    // 5) Clamp integral to reasonable bounds
    m_integral = std::clamp(m_integral, -m_outputLimit / m_ki, m_outputLimit / m_ki);

    // 6) Recalculate output with updated integral
    output = m_kp * error + m_ki * m_integral + m_kd * derivative;

    // 7) Clamp final output to limits
    output = std::clamp(output, -m_outputLimit, m_outputLimit);

    // 8) Store error for next iteration
    m_previousError = error;

    return output;
}

void PIDController::reset() {
    m_integral = 0.0;
    m_previousError = 0.0;
    m_firstRun = true;
}
