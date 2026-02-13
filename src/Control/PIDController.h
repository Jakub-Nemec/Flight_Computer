#pragma once

class PIDController {
public:
    // Constructor with PID gains and output limit
    explicit PIDController(double kp, double ki = 0.0, double kd = 0.0, double outputLimit = 1.0);

    // Compute PID output
    // setpoint: desired value
    // measurement: actual value
    // dt: time step in seconds
    // returns: computed control signal (torque)
    double compute(double setpoint, double measurement, double dt);

    // Reset integral and derivative history
    void reset();

private:
    double m_kp;
    double m_ki;
    double m_kd;
    double m_integral = 0.0;
    double m_previousError = 0.0;
    double m_outputLimit = 1.0;
    bool m_firstRun = true;
};
