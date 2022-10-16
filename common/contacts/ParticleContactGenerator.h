#pragma once
#include <ParticleContact.h>

class ParticleContactGenerator {

public :

	virtual unsigned int addContact(ParticleContact* _contact, unsigned int _limit) const = 0;

};

