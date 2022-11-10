#include "PhysicWorld.h"
#include "Particle.hpp"
#include "GravityForceGenerator.h"
#include "NaiveParticleContactGenerator.h"
#include "ParticleLink.h"
#include "ParticleRod.h"
#include "ParticleCable.h"

/*-------------- CONSTRUCTORS --------------*/

PhysicWorld::PhysicWorld()
{
	const int arraySize = 10;
	/* hard-code max contacts per frame */
	maxContacts = arraySize;

	// init NaiveParticleContactGenerator
	NaiveParticleContactGenerator* npcg = new NaiveParticleContactGenerator(&particles);
	//ParticleCable* pc = new ParticleCable();
	contactGenerators.push_back(npcg);
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
	contacts = vector<ParticleContact*>(); // reset our vector of particle contact
	vector<ParticleContactGenerator*>::iterator ptr; //declare iterator
	for (ptr = contactGenerators.begin(); ptr < contactGenerators.end(); ptr++) {
		unsigned used = (*ptr)->addContact(&contacts, limit);
		limit -= used;
		if (limit <= 0) break;
	}
	
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

	if (usedContacts > 0) {
		contactResolver.setIterations(usedContacts * 2);
		contactResolver.resolveContacts(&contacts, usedContacts, _duration);
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
	delete _targetParticle;
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

void PhysicWorld::addForceEntry(Particle* _newParticle, ObjectForceGenerator* fg) {
	particleForceRegistry.addForceEntry(_newParticle, fg);
}

void PhysicWorld::removeForceEntry(Particle* _targetParticle, ObjectForceGenerator* _targetForceGenerator) {
	particleForceRegistry.removeForceEntry(_targetParticle, _targetForceGenerator);
}



/*-------------- METHODS CONTACT GENERATOR ---------------*/
void PhysicWorld::addContactGenerator(ParticleContactGenerator* _contactGenerator) {
	contactGenerators.push_back(_contactGenerator);
}