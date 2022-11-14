#pragma once
#include <ParticleLink.h>

const float DEFAULT_MAX_LENGHT = 2.0f;
const float DEFAULT_RESTITUTION = 0.0f;

/* Link a pair of particles, generating a contact if they stray to far apart */

class ParticleCable : public ParticleLink {

protected:

	float maxLenght;
	float restitution;

public:

	ParticleCable();
	ParticleCable(Particle* _particle[2]);
	ParticleCable(float _maxLenght, float _restitution);
	ParticleCable(float _maxLenght, float _restitution, Particle* _particle[2]);

	unsigned int addContact(vector<ParticleContact*>* _contact, unsigned int _limit) const;
	bool particleIsInvolved(Particle* _particle);
	string type();
};

