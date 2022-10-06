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

	void updateForce(float _duration); 
	void addForceEntry(Particle* _particule, ParticleForceGenerator* _forceGenerator);
	void removeForceEntry(Particle* _particule, ParticleForceGenerator* _forceGenerator);
	void removeAllForceEntryForParticle(Particle particle);
	void clear();

};