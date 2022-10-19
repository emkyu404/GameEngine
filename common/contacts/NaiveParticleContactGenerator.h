#pragma once

#include <ParticleContactGenerator.h>
#include <vector>

using namespace std;

const float DEFAULT_RADIUS = 1.0f;

class NaiveParticleContactGenerator : public ParticleContactGenerator
{
	float radius;
	vector<Particle*>* particles;

public:

	NaiveParticleContactGenerator();
	NaiveParticleContactGenerator(float _radius);
	NaiveParticleContactGenerator(float _radius, vector<Particle*>* _particles);
	NaiveParticleContactGenerator(vector<Particle*>* _particles);
	unsigned int addContact(ParticleContact* _contact, unsigned int _limit) const;
	bool particleIsInvolved(Particle* _particle);
	string type();
};