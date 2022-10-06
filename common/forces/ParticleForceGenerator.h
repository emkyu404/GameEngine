#pragma once

#include "Particle.hpp"

class ParticleForceGenerator
{

public:

	virtual void UpdateForce(Particle*, float duration) =  0; 

};
