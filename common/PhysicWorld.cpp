#include "PhysicWorld.h"
#include "Particle.hpp"


PhysicWorld::PhysicWorld()
{
}


PhysicWorld* PhysicWorld::singleton = nullptr;;

/*-------------- METHODS --------------*/

void PhysicWorld::applyForces(float _duration) 
{
	// if no particle in the World
	if (particles.size() <= 0) {
		return;
	}
	particleForceRegistry.UpdateForce(_duration);
}

void PhysicWorld::addParticle(Particle _newParticule) 
{
	particles.push_back(_newParticule);
	printf("Add Particle");
}

void PhysicWorld::removeParticle() {
	particles.pop_back();
}

void PhysicWorld::clear() {
	particles.clear();
}

/* return size of vector particles */
int PhysicWorld::numberOfParticles()
{
	return particles.size();
}

vector<Particle> PhysicWorld::getParticles() 
{
	return particles;
}

PhysicWorld* PhysicWorld::getInstance() {
	if (singleton == nullptr) {
		singleton = new PhysicWorld();
	}
	return singleton;
}