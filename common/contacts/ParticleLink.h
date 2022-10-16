#pragma once
#include <ParticleContactGenerator.h>
#include <vector>

const float DEFAULT_LENGHT = 1.0f;

class ParticleLink : public ParticleContactGenerator {

public :

	Particle* particle[2];

	ParticleLink();
	ParticleLink(vector<Particle*> _particles);

	float currentLenght() const;
	unsigned int addContact(ParticleContact* _contact, unsigned int _limit) const = 0;
};

