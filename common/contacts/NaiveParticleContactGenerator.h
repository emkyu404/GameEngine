#include <ParticleContactGenerator.h>
#include <vector>

using namespace std;

class NaiveParticleGenerator : public ParticleContactGenerator
{
	float radius;
	vector<Particle*> particles;

	unsigned int addContact(ParticleContact* contac, unsigned int limit) const;

};