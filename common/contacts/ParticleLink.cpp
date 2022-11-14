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

bool ParticleLink::particleIsInvolved(Particle* _particle)
{
	return true; // ParticleLink gets all particules of our world, always return true
}

string ParticleLink::type()
{
	return "ParticleLink";
}
