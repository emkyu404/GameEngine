#pragma once
#include <ParticleContactGenerator.h>

class ParticleLink : public ParticleContactGenerator {

public :

	Particle* particle[2];

	ParticleLink();
	ParticleLink(Particle* _particles[2]);

	float currentLenght() const;
	unsigned int addContact(vector<ParticleContact*>* _contact, unsigned int _limit) const = 0;
};

