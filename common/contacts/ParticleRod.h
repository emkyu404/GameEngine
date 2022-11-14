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
	ParticleRod(Particle* _particle[2]);
	ParticleRod(float _lenght);
	ParticleRod(float _lenght, Particle* _particle[2]);

	unsigned int addContact(vector<ParticleContact*>* _contact, unsigned int _limit) const;
	bool particleIsInvolved(Particle* _particle);
	string type();
};

