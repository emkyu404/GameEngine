#include "ParticleCable.h"

ParticleCable::ParticleCable()
	: ParticleCable(DEFAULT_MAX_LENGHT, DEFAULT_RESTITUTION) {
}

ParticleCable::ParticleCable(float _maxLenght)
	: ParticleCable(_maxLenght, DEFAULT_RESTITUTION) {
}

/*
ParticleCable::ParticleCable(float _restitution)
	: ParticleCable(DEFAULT_MAX_LENGHT, _restitution) {
}
*/

ParticleCable::ParticleCable(float _maxLenght, float _restitution) {
	maxLenght = _maxLenght;
	restitution = _restitution;
}

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