//
// Created by Jakub Němec on 13.02.2026.
//

#include "RigidBody1D.h"

#include <cassert>

RigidBody1D::RigidBody1D(double momentOfInertia)
	: m_angle(0.0), m_angularVelocity(0.0), m_momentOfInertia(momentOfInertia), m_appliedTorque(0.0)
{
	// Moment of inertia must be positive
	assert(m_momentOfInertia > 0.0);
}

void RigidBody1D::setTorque(double torque) {
	m_appliedTorque = torque;
}

void RigidBody1D::update(double dt) {
	if (dt <= 0.0) return;

	// Angular acceleration: alpha = tau / I
	double alpha = m_appliedTorque / m_momentOfInertia;

	// Integrate angular velocity (explicit Euler)
	m_angularVelocity += alpha * dt;

	// Integrate angle from angular velocity
	m_angle += m_angularVelocity * dt;
}

double RigidBody1D::getAngularVelocity() const {
	return m_angularVelocity;
}

void RigidBody1D::setAngularVelocity(double omega) {
	m_angularVelocity = omega;
}

double RigidBody1D::getAngle() const {
	return m_angle;
}

void RigidBody1D::setAngle(double angle) {
	m_angle = angle;
}