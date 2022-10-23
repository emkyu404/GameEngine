#include "ParticleLink.h"

ParticleLink::ParticleLink() {
}

ParticleLink::ParticleLink(Particle* _particle[2]) {
	particle[0] = _particle[0];
	particle[1] = _particle[1];
}

float ParticleLink::currentLenght() const {
	Vector3D relativePos = particle[0]->getPosition() - particle[1]->getPosition();
	return relativePos.norm();
}

unsigned int ParticleLink::addContact(vector<ParticleContact*>* _contactArray, unsigned _limit) const {

	return 0;
}

bool ParticleLink::particleIsInvolved(Particle* _particle)
{
	return true; // ParticleLink gets all particules of our world, always return true
}

string ParticleLink::type()
{
	return "ParticleLink";
}
