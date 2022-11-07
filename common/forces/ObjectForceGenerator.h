#pragma once

#include "Particle.hpp"

class ObjectForceGenerator
{

public:

	virtual void updateForce(PhysicObject*, float duration) =  0; 

};
