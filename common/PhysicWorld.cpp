#include "PhysicWorld.h"
#include "Particle.hpp"
#include "ParticleGravity.h"

/*-------------- CONSTRUCTORS --------------*/

PhysicWorld::PhysicWorld()
{
}

PhysicWorld* PhysicWorld::singleton = nullptr;;

PhysicWorld* PhysicWorld::getInstance() {
	if (singleton == nullptr) {
		singleton = new PhysicWorld();
	}
	return singleton;
}

/*-------------- GETTERS --------------*/

Particle* PhysicWorld::getParticle(int indexParticle) {
	return particles[indexParticle];
}

vector<Particle*> PhysicWorld::getParticles() {
	return particles;
}

int PhysicWorld::getNumberOfParticles() {
	return particles.size();
}

/*-------------- GENERAL METHOD --------------*/

void PhysicWorld::applyForces(float _duration) {
	if (particles.size() <= 0) {
		return;
	}

	particleForceRegistry.updateForce(_duration);
	for (Particle* particle : particles) {
		particle->integrate(_duration);
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

/*-------------- METHODS FORCES --------------*/

void PhysicWorld::addForceEntry(Particle* _newParticle, ParticleForceGenerator* fg) {
	particleForceRegistry.addForceEntry(_newParticle, fg);
}

void PhysicWorld::removeForceEntry(Particle* _targetParticle, ParticleForceGenerator* _targetForceGenerator) {
	particleForceRegistry.removeForceEntry(_targetParticle, _targetForceGenerator);
}