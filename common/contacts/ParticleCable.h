#pragma once
#include <ParticleLink.h>

class ParticleCable : public ParticleLink
{
public:
	float maxLenght;
	float restitution;
	unsigned int addContact(ParticleContact* _contact, unsigned int _limit) const;

};

