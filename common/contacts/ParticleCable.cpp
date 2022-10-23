#include "ParticleCable.h"

ParticleCable::ParticleCable()
	: ParticleCable(DEFAULT_MAX_LENGHT, DEFAULT_RESTITUTION) {
}

ParticleCable::ParticleCable(float _maxLenght, float _restitution) {
	maxLenght = _maxLenght;
	restitution = _restitution;
}

unsigned int ParticleCable::addContact(vector<ParticleContact*>* _contact, unsigned int _limit) const {

	float lenght = currentLenght();

	if (lenght < maxLenght) {
		return 0;
	}

	ParticleContact* newContact = new ParticleContact(); //create new contact

	newContact->particle[0] = particle[0];
	newContact->particle[1] = particle[1];

	Vector3D normal = particle[1]->getPosition() - particle[0]->getPosition();
	normal.normalize();
	newContact->contactNormal = normal;

	newContact->penetration = lenght - maxLenght;
	newContact->restitution = restitution;

	_contact->push_back(newContact);
	return 1;

}

bool ParticleCable::particleIsInvolved(Particle* _particle)
{
	return true; // ParticleCable gets all particules of our world, always return true
}

string ParticleCable::type()
{
	return "ParticleCable";
}
