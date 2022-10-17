#pragma once
#include <ParticleLink.h>

const float DEFAULT_LENGHT = 1.0f;

class ParticleRod : public ParticleLink {

	ParticleRod();
	ParticleRod(float _lenght);

	float lenght;
	unsigned int addContact(ParticleContact* _contact, unsigned int _limit) const;
};

