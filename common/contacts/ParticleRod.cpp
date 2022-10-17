#include "ParticleRod.h"

ParticleRod::ParticleRod()
	: ParticleRod(DEFAULT_LENGHT) {
}

ParticleRod::ParticleRod(float _lenght) {
	lenght = _lenght;
}

unsigned ParticleRod::addContact(ParticleContact* contact, unsigned int) const {
	float currentLen = currentLenght();

	if (currentLen == lenght) {
		return 0;
	}

	contact->particle[0] = particle[0];
	contact->particle[1] = particle[1];

	Vector3D normal = particle[1]->getPosition() - particle[1]->getPosition();
	normal.normalize();

	if (currentLen > lenght) {
		contact->contactNormal = normal;
		contact->penetration = currentLen - lenght;
	}
	else {
		contact->contactNormal = normal * -1;
		contact->penetration = lenght - currentLen;
	}

	contact->restitution = 0;

	return 1;

}