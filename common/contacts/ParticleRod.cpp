#include "ParticleRod.h"

ParticleRod::ParticleRod()
	: ParticleRod(DEFAULT_LENGHT) {
}

ParticleRod::ParticleRod(float _lenght) {
	lenght = _lenght;
}

unsigned int ParticleRod::addContact(vector<ParticleContact*>* _contact, unsigned int _limit) const {
	float currentLen = currentLenght();

	if (currentLen == lenght) {
		return 0;
	}
	ParticleContact* newContact = new ParticleContact(); //create new contact

	newContact->particle[0] = particle[0];
	newContact->particle[1] = particle[1];

	Vector3D normal = particle[1]->getPosition() - particle[1]->getPosition();
	normal.normalize();

	if (currentLen > lenght) {
		newContact->contactNormal = normal;
		newContact->penetration = currentLen - lenght;
	}
	else {
		newContact->contactNormal = normal * -1;
		newContact->penetration = lenght - currentLen;
	}

	newContact->restitution = 0;

	_contact->push_back(newContact);

	return 1;

}

bool ParticleRod::particleIsInvolved(Particle* _particle)
{
	return true; // ParticleRod gets all particules of our world, always return true
}

string ParticleRod::type()
{
	return "ParticleRod";
}
