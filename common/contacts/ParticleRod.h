#pragma once
#include <ParticleLink.h>

class ParticleRod : public ParticleLink {

	float lenght;
	unsigned int addContact(ParticleContact* _contact, unsigned int _limit) const;

};

