#pragma once

#include "Particle.hpp"

class ParticleForceGenerator
{

public:

	virtual void updateForce(Particle*, float duration) =  0; 

};
