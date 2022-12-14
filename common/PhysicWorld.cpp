#include "PhysicWorld.h"
#include "Particle.hpp"
#include "GravityForceGenerator.h"
#include "NaiveParticleContactGenerator.h"
#include "ParticleLink.h"
#include "ParticleRod.h"
#include "ParticleCable.h"
#include "Box.h"
#include "Octree.h"

/*-------------- CONSTRUCTORS --------------*/

PhysicWorld::PhysicWorld()
{
	isPaused = false;
	//const int arraySize = 10;
	/* hard-code max contacts per frame */
	//maxContacts = arraySize;

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


/* OLD VERSION WITH PARTICLE - TO BE CHANGED
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
}*/

void PhysicWorld::integrate(float _duration) {
	for (PhysicObject* physicObject : physicObjects) {
		physicObject->integrate(_duration);
	}
}

vector<CollisionData> PhysicWorld::generateContacts() {
	//Broad phase
	Octree octree = Octree();
	octree.createOctree(Vector3D(0, 0, 0), 10.0f, 4, getRigidBodies());
	vector<vector<RigidBody*>> rigidbodies = octree.getRigidbodies();

	// Narrow Phase
	vector<CollisionData> collisions;

	for (int iRigid = 0; iRigid < rigidbodies.size(); iRigid++)
	{
		vector<RigidBody*> potentialContacts = rigidbodies[iRigid]; // To be changed after broad phase

		for (int i = 0; i < potentialContacts.size() - 1; i++) {
			if (primitives.count(potentialContacts[i])) {
				vector<Primitive*> primitives1 = primitives[potentialContacts[i]];
				for (int j = 1; j < potentialContacts.size(); j++) {
					if (primitives.count(potentialContacts[j])) {
						vector<Primitive*> primitives2 = primitives[potentialContacts[j]];
						//compare all primitives to each other
						for (int k = 0; k < primitives1.size(); k++) {
							for (int l = 0; l < primitives2.size(); l++) {
								vector<CollisionData> p_collisions = primitives1[k]->evaluateCollision(primitives2[l]);
								if (p_collisions.size() > 0) {
									collisions.insert(collisions.begin(), p_collisions.begin(), p_collisions.end());
								}
							}
						}
					}
				}
			}
		}
	}

	if (collisions.size() > 0)
	{
		printf("CONTACT - List octree size %d\n", rigidbodies.size()); 

		for (int i = 0; i < rigidbodies.size(); i++)
		{
			printf("CONTACT - Size list collision %d\n", rigidbodies[i].size());
		}
	}

	return collisions;
}

void PhysicWorld::runPhysics(float _duration) {
	if (isPaused) {
		return;
	}

	if (physicObjects.size() <= 0) {
		return;
	}

	// First, apply force generators
	forceRegistry.updateForce(_duration);

	//Then integrate the objects
	integrate(_duration);

	contacts = generateContacts();

	if (contacts.size() > 0) {
		Pause(); // will pause run physics
	}

	/* OLD VERSION WITH PARTICLE
	// Generate contacts
	int usedContacts = generateContacts();

	//Resolve them

	if (usedContacts > 0) {
		contactResolver.setIterations(usedContacts * 2);
		contactResolver.resolveContacts(&contacts, usedContacts, _duration);
	}*/
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
	addRigidBody(_initialPosition, Vector3D(1, 1, 1));
}

void PhysicWorld::addRigidBody(Vector3D _initialPosition, Vector3D _scale) {
	RigidBody* _newRigidBody = new RigidBody(_initialPosition, _scale);
	_newRigidBody->setMass(1);
	physicObjects.push_back(_newRigidBody);
	Box* boxPrimitive = new Box(_newRigidBody, _newRigidBody->getTransformMatrix(), _scale);

	// Add primitive
	vector<Primitive*> rigidBodyPrimitives;
	rigidBodyPrimitives.push_back(boxPrimitive);
	primitives.insert({ _newRigidBody, rigidBodyPrimitives });
}


void PhysicWorld::addRigidBody(Vector3D _initialPosition, float _mass) {
	RigidBody* _newRigidBody = new RigidBody(_initialPosition);
	_newRigidBody->setMass(_mass);
	physicObjects.push_back(_newRigidBody)
;}

void PhysicWorld::addRigidBody(RigidBody* _newRigidBody, Primitive* primitive) {
	physicObjects.push_back(_newRigidBody);

	// Add primitive
	vector<Primitive*> rigidBodyPrimitives;
	rigidBodyPrimitives.push_back(primitive);
	primitives.insert({ _newRigidBody, rigidBodyPrimitives });
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

vector<CollisionData> PhysicWorld::getContacts()
{
	return contacts;
}

void PhysicWorld::Resume() {
	isPaused = false;
}

void PhysicWorld::Pause() {
	isPaused = true;
}



/*-------------- METHODS CONTACT GENERATOR ---------------*/
/*
void PhysicWorld::addContactGenerator(ParticleContactGenerator* _contactGenerator) {
	contactGenerators.push_back(_contactGenerator);
}
*/