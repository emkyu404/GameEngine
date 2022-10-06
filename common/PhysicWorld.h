#pragma once

#include <vector>
#include "Particle.hpp";
#include "ParticleForceRegistry.h";
#include <ParticleContact.h>


using namespace std;

class PhysicWorld
{
private:
	static PhysicWorld* singleton; // singleton design pattern as we have only one instance of PhysicWorld that should be runnning

	vector<Particle*> particles; // list of particles
	vector<ParticleContact*> particlesContacts; // list of contacts
	ParticleForceRegistry particleForceRegistry;

public:

	PhysicWorld();
	/* Methods */
	void handleContacts();
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