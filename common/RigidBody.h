#pragma once
#include "PhysicObject.h"
#include "Vector3D.hpp"
#include "Matrix34.h"

class RigidBody : public PhysicObject
{
private:
	// Angular velocity of the rigid body
	Vector3D rotation;

	// calculate transform matrix from orientation and rotation
	Matrix34 transformMatrix;

public:
	void integrate(float deltaTime);
	void reset();
	void addForce(Vector3D);
	void clearForce();
};