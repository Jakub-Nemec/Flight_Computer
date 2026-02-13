//
// Created by Jakub Němec on 12.02.2026.
//

#ifndef FLIGHT_COMPUTER_GYROSENSOR_H
#define FLIGHT_COMPUTER_GYROSENSOR_H


class RigidBody1D; // forward declaration

class GyroSensor {
public:
	// Construct sensor bound to a dynamics model (RigidBody1D)
	explicit GyroSensor(RigidBody1D &body);

	// Read angular velocity (rad/s) from the dynamics model
	double readAngularVelocity() const;

private:
	RigidBody1D &m_body;
};


#endif //FLIGHT_COMPUTER_GYROSENSOR_H