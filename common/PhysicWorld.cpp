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
	//NaiveParticleContactGenerator* npcg = new NaiveParticleContactGenerator(&particles);
	//ParticleCable* pc = new ParticleCable();
	//contactGenerators.push_back(npcg);
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
	for (PhysicObject* physicObject : physicObjects) {
		physicObject->integrate(_duration);
	}
}

void PhysicWorld::runPhysics(float _duration) {
	if (physicObjects.size() <= 0) {
		return;
	}

	// First, apply force generators
	forceRegistry.updateForce(_duration);

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
	physicObjects.push_back(_newParticle);
}

void PhysicWorld::addParticle(Vector3D _initialPosition) {
	Particle* _newParticle = new Particle(_initialPosition);
	_newParticle->setMass(1);
	physicObjects.push_back(_newParticle);
}

void PhysicWorld::removePhysicObject(PhysicObject* _target) {
	forceRegistry.removeAllForceEntryForPhysicObject(_target);
	physicObjects.erase(
		remove_if(
			physicObjects.begin(),
			physicObjects.end(),
			[&](const PhysicObject* p)
			{ return p == _target;
			}),
		physicObjects.end()
				);
	delete _target;
}

vector<Particle*> PhysicWorld::getParticles()
{
	vector<PhysicObject*> physicObjects = getPhysicObjects();
	vector<Particle*> particles; 

	for (PhysicObject* physicObject : physicObjects)
	{
		Particle* particle = dynamic_cast<Particle*>(physicObject); 
		if (particle != nullptr)
		{
			particles.push_back(particle); 
		}
	}

	return particles;
}

int PhysicWorld::getNumberOfParticles() {
	vector<Particle*> particles = getParticles(); 
	return particles.size(); 
}

/*-------------- METHODS RIGIDBODIES --------------*/

void PhysicWorld::addRigidBody() {
	RigidBody* _newRigidBody = new RigidBody();
	_newRigidBody->setMass(1);
	physicObjects.push_back(_newRigidBody);
}

void PhysicWorld::addRigidBody(Vector3D _initialPosition) {
	RigidBody* _newRigidBody = new RigidBody(_initialPosition);
	_newRigidBody->setMass(1);
	physicObjects.push_back(_newRigidBody);
}


void PhysicWorld::addRigidBody(Vector3D _initialPosition, float _mass) {
	RigidBody* _newRigidBody = new RigidBody(_initialPosition);
	_newRigidBody->setMass(_mass);
	physicObjects.push_back(_newRigidBody);
}

vector<RigidBody*> PhysicWorld::getRigidBodies()
{
	vector<PhysicObject*> physicObjects = getPhysicObjects();
	vector<RigidBody*> rigidbodies;

	for (PhysicObject* physicObject : physicObjects)
	{
		RigidBody* rigidbody = dynamic_cast<RigidBody*>(physicObject);
		if (rigidbody != nullptr)
		{
			rigidbodies.push_back(rigidbody);
		}
	}

	return rigidbodies;
}

int PhysicWorld::getNumberOfRigidBodies() {
	vector<RigidBody*> rigidbodies = getRigidBodies();
	return rigidbodies.size();
}

void PhysicWorld::clearPhysicObjects() {
	forceRegistry.clear();
}

vector<PhysicObject*> PhysicWorld::getPhysicObjects() {
	return physicObjects;
}

int PhysicWorld::getNumberOfPhysicObject() {
	return physicObjects.size();
}

PhysicObject* PhysicWorld::getPhysicObject(int _index) {
	return physicObjects[_index];
}

/*-------------- METHODS FORCES --------------*/

void PhysicWorld::addForceEntry(PhysicObject* _newPhysicObject, ObjectForceGenerator* fg) {
	forceRegistry.addForceEntry(_newPhysicObject, fg);
}

void PhysicWorld::removeForceEntry(PhysicObject* _targetPhysicObject, ObjectForceGenerator* _targetForceGenerator) {
	forceRegistry.removeForceEntry(_targetPhysicObject, _targetForceGenerator);
}



/*-------------- METHODS CONTACT GENERATOR ---------------*/
void PhysicWorld::addContactGenerator(ParticleContactGenerator* _contactGenerator) {
	contactGenerators.push_back(_contactGenerator);
}