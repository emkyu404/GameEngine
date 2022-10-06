#pragma once
#include <ParticleContact.h>

class ParticleContactResolver {

protected :

	unsigned int iterations;
	unsigned int iterationsUsed;

public :

	void resolveContacts(ParticleContact* _contactArray, unsigned int _numContacts, float _duration);
	void setIterations(unsigned _iterations);
};