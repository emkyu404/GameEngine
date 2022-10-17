#pragma once

#include <vector>
#include "Particle.hpp"
#include "ParticleForceRegistry.h"
#include <ParticleContact.h>
#include "ParticleContactResolver.h"
#include "ParticleContactGenerator.h"

using namespace std;

class PhysicWorld
{
private:
	static PhysicWorld* singleton; // singleton design pattern as we have only one instance of PhysicWorld that should be running

	
	vector<Particle*> particles; // list of particles
	ParticleForceRegistry particleForceRegistry;
	
	ParticleContactResolver contactResolver; // hold resolver of contact
	vector<ParticleContactGenerator*> contactGenerators;

	ParticleContact* contacts; // hold list of contact

	unsigned int maxContacts; // maximum of contact possible => size of contact array

public:

	/*-------------- CONSTRUCTORS --------------*/

	PhysicWorld();
	static PhysicWorld* getInstance();

	/*-------------- GETTERS --------------*/

	Particle* getParticle(int indexParticle);
	vector<Particle*> getParticles();
	int getNumberOfParticles();

	/*-------------- GENERAL METHOD --------------*/

	void runPhysics(float _duration);
	void integrate(float _duration);
	unsigned generateContacts();

	/*-------------- METHODS PARTICLES --------------*/
	/* Methods */

	void addParticle(); 
	void addParticle(Vector3D _initialPosition);
	void removeParticle(Particle* _targetParticle);

	void clearParticles();

	/*-------------- METHODS FORCES --------------*/

	void addForceEntry(Particle* _newParticle, ParticleForceGenerator* _forceGenerator);
	void removeForceEntry(Particle* _targetParticle, ParticleForceGenerator* _targetForceGenerator);

	/*-------------- METHODS CONTACT GENERATOR --------------*/

	void addContactGenerator(ParticleContactGenerator* _contactGenerator);
};