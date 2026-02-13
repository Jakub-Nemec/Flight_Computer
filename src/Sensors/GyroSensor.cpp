//
// Created by Jakub Němec on 12.02.2026.
//

#include "GyroSensor.h"
#include "Dynamics/RigidBody1D.h"

GyroSensor::GyroSensor(RigidBody1D &body)
	: m_body(body)
{
}

double GyroSensor::readAngularVelocity() const {
	// For now, return the model's true angular velocity without noise
	return m_body.getAngularVelocity();
}