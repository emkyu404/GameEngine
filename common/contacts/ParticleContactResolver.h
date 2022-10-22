#pragma once
#include <ParticleContact.h>
#include <vector>

using namespace std;

class ParticleContactResolver {

protected :

	unsigned int iterations;
	unsigned int iterationsUsed;

public :

	void resolveContacts(vector<ParticleContact*>* _contactArray, unsigned int _numContacts, float _duration);
	void setIterations(unsigned _iterations);
};