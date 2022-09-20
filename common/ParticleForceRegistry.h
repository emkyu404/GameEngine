#pragma once

#include "ParticleForceGenerator.h"
#include "Particle.hpp"
#include "Vector3D.hpp"

class ParticleForceRegistry
{
private:

	struct ParticleForceEntry
	{
		Particle* particle; 
		ParticleForceGenerator* forceGenerator; 
	};

public:

	/*-------------- METHODES --------------*/

	void UpdateForce(float duration); 
};