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

	/*-------------- CONSTRUCTORS --------------*/

	PhysicWorld();
	static PhysicWorld* getInstance();

	/*-------------- GETTERS --------------*/

	Particle* getParticle(int indexParticle);
	vector<Particle*> getParticles();
	int getNumberOfParticles();

	/*-------------- GENERAL METHOD --------------*/

	void applyForces(float _duration);

	/*-------------- METHODS PARTICLES --------------*/
	/* Methods */
	void handleContacts();
	void addParticle(); 
	void addParticle(Vector3D _initialPosition);
	void removeParticle(Particle* _targetParticle);

	void clearParticles();
	
	/*-------------- METHODS FORCES --------------*/

	void addForceEntry(Particle* _newParticle, ParticleForceGenerator* _forceGenerator);
	void removeForceEntry(Particle* _targetParticle, ParticleForceGenerator* _targetForceGenerator);
};