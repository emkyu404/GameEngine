#include <ParticleContactGenerator.h>


class ParticleLink : public ParticleContactGenerator {

public :

	Particle* particle[2];
	float currentLenght() const;
	unsigned int addContact(ParticleContact* _contact, unsigned int _limit) const = 0;

	ParticleLink();
	//ParticleLink(vector<Particles*>);


};

