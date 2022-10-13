#include "ParticleCable.h"

unsigned ParticleCable::addContact(ParticleContact* contact, unsigned limit) const {

	float lenght = currentLenght();

	if (lenght < maxLenght) {
		return 0;
	}

	contact->particle[0] = particle[0];
	contact->particle[1] = particle[1];

	Vector3D normal = particle[1]->getPosition() - particle[0]->getPosition();
	normal.normalize();
	contact->contactNormal = normal;

	contact->penetration = lenght - maxLenght;
	contact->restitution = restitution;

	return 1;

}