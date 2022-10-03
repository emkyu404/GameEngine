#pragma once

#include <vector>
#include "Particle.hpp";
#include "ParticleForceRegistry.h";


using namespace std;

class PhysicWorld
{
private:
	static PhysicWorld* singleton; // singleton design pattern
	vector<Particle*> particles; // list of particles 
	ParticleForceRegistry particleForceRegistry;


public:

	PhysicWorld();
	/* Methods */
	void ApplyForces(float _duration);

	void AddParticle(); 
	void RemoveParticle(Particle* _targetParticle);

	void Clear(); // Remove all particle
	int NumberOfParticles();

	vector<Particle*> getParticles();

	static PhysicWorld* getInstance();

	void AddForceEntry(Particle* _newParticle, ParticleForceGenerator* _forceGenerator);
	void RemoveForceEntry(Particle* _targetParticle, ParticleForceGenerator* _targetForceGenerator);
};