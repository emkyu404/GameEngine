#pragma once
#include "SpringForceGenerator.h"
#include "Vector3D.hpp"


class ParticleSpringForceGenerator : public SpringForceGenerator
{
public:

	/*-------------- METHODES --------------*/

	void updateForce(PhysicObject* particle, float duration);
};