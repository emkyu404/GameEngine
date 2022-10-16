#include "ParticleLink.h"

ParticleLink::ParticleLink() {
	
}

float ParticleLink::currentLenght() const {
	Vector3D relativePos = particle[0]->getPosition() - particle[1]->getPosition();
	return 0.0f;
	//return relativePos.magnitude() ??
}

unsigned ParticleLink::addContact(ParticleContact* contact, unsigned limit) const {

	return 0;
}