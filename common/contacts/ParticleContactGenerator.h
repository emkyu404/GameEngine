#pragma once
#include <ParticleContact.h>
#include <string>

class ParticleContactGenerator {

public :

	virtual unsigned int addContact(ParticleContact* _contact, unsigned int _limit) const = 0;
	virtual bool particleIsInvolved(Particle* _particle) = 0;
	virtual string type() = 0;

};

