#pragma once

#include <Vector3D.hpp>

class PhysicObject {

protected:
	Vector3D position;
	Vector3D initialPosition; // useful for simulation to place the particle where it is;
	Vector3D velocity;
	Vector3D acceleration;
	float inverseMass;
	float damping;
	Vector3D forceAccumulator;

public:
	virtual void integrate(float _deltaTime) = 0;
	virtual void addForce(Vector3D _force) = 0;
	virtual void clearForce() = 0;

	Vector3D getPosition();
	Vector3D getInitialPosition() ;
	Vector3D getVelocity();
	Vector3D getAcceleration();
	float getMass();
	float getInverseMass();

	void setPosition(Vector3D);
	void initializePosition(Vector3D);
	void setVelocity(Vector3D);
	void setAcceleration(Vector3D);
	void setMass(float);
	void setInverseMass(float);
};