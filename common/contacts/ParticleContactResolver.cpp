#include <ParticleContactResolver.h>
#include <vector>

using namespace std;

void ParticleContactResolver::resolveContacts(vector<ParticleContact*>* _contactArray, unsigned int _numContacts, float _duration) {
	iterationsUsed = 0;
	while (iterationsUsed < iterations) {
		float max = FLT_MAX;
		int maxIndex = 0;
		// Search for contact with maximum seperating velocity
		for (int i = 0; i < _contactArray->size(); i++) {
			float sepVel = _contactArray->at(i)->calculateSeparatingVelocity();
			if (sepVel < max && sepVel < 0 || _contactArray->at(i)->penetration > 0) {
				max = sepVel;
				maxIndex = i;
			}
		}
		_contactArray->at(maxIndex)->resolve(_duration);
		_contactArray->erase(_contactArray->begin() + maxIndex); // remove the contact from array
		iterationsUsed++;

		if (_contactArray->empty()) {
			printf("All contact resolved\n");
			return;
		}
	}
}

void ParticleContactResolver::setIterations(unsigned _iterations) {
	this->iterations = _iterations;
}
