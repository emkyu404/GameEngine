#include <ParticleContactResolver.h>

void ParticleContactResolver::resolveContacts(ParticleContact* _contactArray, unsigned int _numContacts, float _duration) {
	unsigned i;

	iterationsUsed = 0;
	while (iterationsUsed < iterations) {
		float max = FLT_MAX;
		unsigned maxIndex = _numContacts;

		for (i = 0; i < _numContacts; i++) {
			float sepVel = _contactArray[i].calculateSeparatingVelocity();
			if (sepVel < max && (sepVel < 0 || _contactArray[i].penetration >0)) {
				max = sepVel;
				maxIndex = i;
			}
		}

		if (maxIndex == _numContacts) break;

		_contactArray[maxIndex].resolve(_duration);

		iterationsUsed++;
	}
}

void ParticleContactResolver::setIterations(unsigned _iterations) {
	this->iterations = _iterations;
}
