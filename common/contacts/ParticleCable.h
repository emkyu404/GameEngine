#pragma once
#include <ParticleLink.h>

const float DEFAULT_MAX_LENGHT = 2.0f;
const float DEFAULT_RESTITUTION = 0.0f;

class ParticleCable : public ParticleLink {

public:

	ParticleCable();
	ParticleCable(float _maxLenght);
	//ParticleCable(float _restitution);
	ParticleCable(float _maxLenght, float _restitution);

	float maxLenght;
	float restitution;
	unsigned int addContact(ParticleContact* _contact, unsigned int _limit) const;
};

