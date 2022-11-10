#pragma once

#include <vector>
#include "Particle.hpp"
#include "ObjectForceRegistry.h"
#include <ParticleContact.h>
#include "ParticleContactResolver.h"
#include "ParticleContactGenerator.h"

using namespace std;

class PhysicWorld
{
private:
	static PhysicWorld* singleton; // singleton design pattern as we have only one instance of PhysicWorld that should be running

	
	vector<PhysicObject*> physicObjects; // list of physicsObject
	ObjectForceRegistry forceRegistry;


	ParticleContactResolver contactResolver; // hold resolver of contact
	vector<ParticleContactGenerator*> contactGenerators;

	vector<ParticleContact*> contacts;

	unsigned int maxContacts; // maximum of contact possible => size of contact array

public:

	/*-------------- CONSTRUCTORS --------------*/

	PhysicWorld();
	static PhysicWorld* getInstance();

	/*-------------- GETTERS --------------*/

	PhysicObject* getPhysicObject(int indexParticle);
	vector<PhysicObject*> getPhysicObjects();
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

	void addForceEntry(PhysicObject* _newPhysicObject, ObjectForceGenerator* fg);
	void removeForceEntry(PhysicObject* _targetPhysicObject, ObjectForceGenerator* _targetForceGenerator);

	/*-------------- METHODS CONTACT GENERATOR --------------*/

	void addContactGenerator(ParticleContactGenerator* _contactGenerator);
};