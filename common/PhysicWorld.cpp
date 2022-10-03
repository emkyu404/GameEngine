#include "PhysicWorld.h"
#include "Particle.hpp"
#include "ParticleGravity.h"

PhysicWorld::PhysicWorld()
{
}


PhysicWorld* PhysicWorld::singleton = nullptr;;

/*-------------- METHODS --------------*/

void PhysicWorld::ApplyForces(float _duration) 
{
	if (particles.size() <= 0) {
		printf("No particle \n");
		return;
	}
	
	
	particleForceRegistry.UpdateForce(_duration);
	for (Particle* particle : particles) {
		particle->Integrate(_duration);
	}
}

void PhysicWorld::AddParticle(Particle* _newParticule) 
{
	particles.push_back(_newParticule);
}


void PhysicWorld::AddForceEntry(Particle* _newParticule, ParticleForceGenerator* fg) {
	particleForceRegistry.AddForceEntry(_newParticule, fg);
}

void PhysicWorld::RemoveForceEntry(Particle* _targetParticle, ParticleForceGenerator* _targetForceGenerator)
{
	particleForceRegistry.RemoveForceEntry(_targetParticle, _targetForceGenerator);
}

void PhysicWorld::RemoveParticle() {
	//TODO 
	//particles.pop_back();
}

void PhysicWorld::Clear() {
	particleForceRegistry.Clear();
}

/* return size of vector particles */
int PhysicWorld::NumberOfParticles()
{
	return particles.size();
}

vector<Particle*> PhysicWorld::getParticles() 
{
	return particles;
}

PhysicWorld* PhysicWorld::getInstance() {
	if (singleton == nullptr) {
		singleton = new PhysicWorld();
	}
	return singleton;
}