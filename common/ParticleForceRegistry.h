#pragma once

#include <vector>
#include "ParticleForceGenerator.h"
#include "Particle.hpp"
#include "Vector3D.hpp"

using namespace std;

class ParticleForceRegistry
{
private:

	struct ParticleForceEntry
	{
		Particle* particle; 
		ParticleForceGenerator* forceGenerator; 
	};

	using Registry = vector<ParticleForceEntry>;
	Registry m_registry;

public:

	/*-------------- METHODES --------------*/

	void UpdateForce(float duration); 
};