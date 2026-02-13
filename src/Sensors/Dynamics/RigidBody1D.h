//
// Created by Jakub Němec on 13.02.2026.
//

#ifndef FLIGHT_COMPUTER_RIGIDBODY1D_H
#define FLIGHT_COMPUTER_RIGIDBODY1D_H


class RigidBody1D {
public:
	// Create a body with given moment of inertia (default 1.0)
	explicit RigidBody1D(double momentOfInertia = 1.0);

	// Set external torque applied to the body (N·m)
	void setTorque(double torque);

	// Integrate dynamics forward by dt seconds (explicit Euler)
	void update(double dt);

	// Return current angular velocity (rad/s)
	double getAngularVelocity() const;

private:
	double m_angularVelocity = 0.0;
	double m_momentOfInertia = 1.0;
	double m_appliedTorque = 0.0;
};


#endif //FLIGHT_COMPUTER_RIGIDBODY1D_H