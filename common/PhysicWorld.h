#pragma once

#include <vector>
#include "Particle.hpp";
#include "ParticleForceRegistry.h";


using namespace std;

class PhysicWorld
{
private:
	static PhysicWorld* singleton; // singleton design pattern
	vector<Particle> particles; // list of particles 
	ParticleForceRegistry particleForceRegistry;


public:

	PhysicWorld();
	/* Methods */
	void applyForces(float _duration);
	void addParticle(Particle _newParticle);
	void removeParticle();
	void clear();
	int numberOfParticles();

	vector<Particle> getParticles();

	static PhysicWorld* getInstance();

};