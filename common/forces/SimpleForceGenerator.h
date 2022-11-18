#pragma once

#include "ObjectForceGenerator.h"
#include "Vector3D.hpp"

class SimpleForceGenerator : public ObjectForceGenerator
{
protected:
	Vector3D force;
	Vector3D localBodyPoint;

public:

	/*-------------- CONSTRUCTORS --------------*/
	SimpleForceGenerator();
	SimpleForceGenerator(Vector3D force);
	SimpleForceGenerator(Vector3D force, Vector3D localBodyPoint);


	/*-------------- METHODES --------------*/

	void updateForce(PhysicObject*, float duration);
};