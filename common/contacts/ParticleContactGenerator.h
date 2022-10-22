#pragma once
#include <ParticleContact.h>
#include <string>
#include <vector>

using namespace std;

class ParticleContactGenerator {

public :

	virtual unsigned int addContact(vector<ParticleContact*>* _contactArray, unsigned int _limit) const = 0;
	virtual bool particleIsInvolved(Particle* _particle) = 0;
	virtual string type() = 0;

};

