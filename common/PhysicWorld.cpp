#include "PhysicWorld.h"
#include "Particle.hpp"
#include "ParticleGravity.h"
#include "NaiveParticleContactGenerator.h"

/*-------------- CONSTRUCTORS --------------*/

PhysicWorld::PhysicWorld()
{
	/* hard-code max contacts per frame */
	maxContacts = 10;
}

PhysicWorld* PhysicWorld::singleton = nullptr;;

PhysicWorld* PhysicWorld::getInstance() {
	if (singleton == nullptr) {
		singleton = new PhysicWorld();
	}
	return singleton;
}


unsigned PhysicWorld::generateContacts() {
	unsigned limit = maxContacts;
	ParticleContact* nextContact = contacts;

	/*
	for (ParticleContactGenerator contactGenerator : contactGenerators) {
		unsigned used = (g)->addContact(nextContact, limit);
		limit -= used;
		nextContact += used;

		if (limit <= 0) break;
	}
	*/
	return maxContacts - limit;
}

void PhysicWorld::integrate(float _duration) {
	for (Particle* particle : particles) {
		particle->integrate(_duration);
	}
}

void PhysicWorld::runPhysics(float _duration) {
	if (particles.size() <= 0) {
		return;
	}

	// First, apply force generators
	particleForceRegistry.updateForce(_duration);

	//Then integrate the objects
	integrate(_duration);

	// Generate contacts
	int usedContacts = generateContacts();

	//Resolve them

	if (usedContacts) {
		contactResolver.setIterations(usedContacts * 2);
		contactResolver.resolveContacts(contacts, usedContacts, _duration);
	}
}

/*-------------- METHODS PARTICLES --------------*/

void PhysicWorld::addParticle() {
	Particle* _newParticle = new Particle();
	_newParticle->setMass(1);
	particles.push_back(_newParticle);
}

void PhysicWorld::addParticle(Vector3D _initialPosition) {
	Particle* _newParticle = new Particle(_initialPosition);
	_newParticle->setMass(1);
	particles.push_back(_newParticle);
}

void PhysicWorld::removeParticle(Particle* _targetParticle) {
	particles.erase(
		remove_if(
			particles.begin(),
			particles.end(),
			[&](const Particle* p)
			{ return p == _targetParticle;
			}),
		particles.end()
				);
}

void PhysicWorld::clearParticles() {
	particleForceRegistry.clear();
}

vector<Particle*> PhysicWorld::getParticles() {
	return particles;
}

int PhysicWorld::getNumberOfParticles() {
	return particles.size();
}

Particle* PhysicWorld::getParticle(int _index) {
	return particles[_index];
}

/*-------------- METHODS FORCES --------------*/

void PhysicWorld::addForceEntry(Particle* _newParticle, ParticleForceGenerator* fg) {
	particleForceRegistry.addForceEntry(_newParticle, fg);
}

void PhysicWorld::removeForceEntry(Particle* _targetParticle, ParticleForceGenerator* _targetForceGenerator) {
	particleForceRegistry.removeForceEntry(_targetParticle, _targetForceGenerator);
}