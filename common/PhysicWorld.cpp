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
		return;
	}
	
	
	particleForceRegistry.UpdateForce(_duration);
	for (Particle* particle : particles) {
		particle->Integrate(_duration);
	}
}

void PhysicWorld::AddParticle() 
{
	Particle* _newParticle = new Particle();
	_newParticle->SetMass(1);
	particles.push_back(_newParticle);
}

void PhysicWorld::AddParticle(Vector3D _initialPosition)
{
	Particle* _newParticle = new Particle(_initialPosition);
	_newParticle->SetMass(1);
	particles.push_back(_newParticle);
}

void PhysicWorld::RemoveParticle(Particle* _targetParticle)
{
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


void PhysicWorld::AddForceEntry(Particle* _newParticle, ParticleForceGenerator* fg) {
	particleForceRegistry.AddForceEntry(_newParticle, fg);
}

void PhysicWorld::RemoveForceEntry(Particle* _targetParticle, ParticleForceGenerator* _targetForceGenerator)
{
	particleForceRegistry.RemoveForceEntry(_targetParticle, _targetForceGenerator);
}

void PhysicWorld::Clear() {
	particleForceRegistry.Clear();
}

/* return size of vector particles */
int PhysicWorld::NumberOfParticles()
{
	return particles.size();
}

Particle* PhysicWorld::getParticle(int indexParticle)
{
	return particles[indexParticle]; 
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