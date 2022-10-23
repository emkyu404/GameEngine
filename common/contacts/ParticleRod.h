#pragma once
#include <ParticleLink.h>

const float DEFAULT_LENGHT = 1.0f;

/* Link a pair of particles, generating a contact if they stray too 
far apart or too close */

class ParticleRod : public ParticleLink {

protected:

	float lenght;

public :

	ParticleRod();
	ParticleRod(float _lenght);

	unsigned int addContact(vector<ParticleContact*>* _contact, unsigned int _limit) const;
	bool particleIsInvolved(Particle* _particle);
	string type();
};

