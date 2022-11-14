#pragma once
#include <ParticleContactGenerator.h>

/* Links connect two particles together, generating contact if they violate the 
constraints of their link
It is used as a base class for cables and rods and could be used as a base class for 
springs with a limit to their extension */

class ParticleLink : public ParticleContactGenerator {

protected :

	Particle* particle[2];

public :

	ParticleLink();
	ParticleLink(Particle* _particle[2]);

	float currentLenght() const;
	virtual unsigned int addContact(vector<ParticleContact*>* _contact, unsigned int _limit) const = 0;
	bool particleIsInvolved(Particle* _particle);
	string type();
};

