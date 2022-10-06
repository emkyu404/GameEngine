#pragma once
#include <ParticleLink.h>
class ParticleRod : public ParticleLink
{
	float Lenght;
	unsigned int addContact(ParticleContact* _contact, unsigned int _limit) const;

};

