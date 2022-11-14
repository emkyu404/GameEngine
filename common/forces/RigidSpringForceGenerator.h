#pragma once

#include "SpringForceGenerator.h"
#include "RigidBody.h"
#include "Vector3D.hpp"



class RigidSpringForceGenerator : public SpringForceGenerator
{
private:

	Vector3D m_bodyAnchor; 

	// other anchor
	Vector3D m_otherBodyAnchor;

public:

	/*-------------- CONSTRUCTORS --------------*/

	RigidSpringForceGenerator(PhysicObject*, Vector3D, Vector3D);
	RigidSpringForceGenerator(PhysicObject*, float, float, Vector3D, Vector3D);

	/*-------------- METHODES --------------*/

	void updateForce(PhysicObject* rigidbody, float duration);
};