#pragma once

#include <vector>
#include <map>
#include "Particle.hpp"
#include "RigidBody.h"
#include "ObjectForceRegistry.h"
#include <ParticleContact.h>
#include "ParticleContactResolver.h"
#include "ParticleContactGenerator.h"
#include "Primitive.h"

using namespace std;

class PhysicWorld
{
private:
	static PhysicWorld* singleton; // singleton design pattern as we have only one instance of PhysicWorld that should be running

	
	vector<PhysicObject*> physicObjects; // list of physicsObject
	ObjectForceRegistry forceRegistry;
	map<RigidBody*,vector<Primitive*>> primitives; // list of primitives, updated at rigidbodies creation

	vector<CollisionData> contacts;

	bool isPaused;


	//ParticleContactResolver contactResolver; // hold resolver of contact
	//vector<ParticleContactGenerator*> contactGenerators;

	//vector<ParticleContact*> contacts;

	//unsigned int maxContacts; // maximum of contact possible => size of contact array

protected:

	/*-------------- GENERAL METHOD --------------*/

	void integrate(float _duration);
	vector<CollisionData> generateContacts();
	//vector<Node*> broadPhase();
	//vector<Contact*> narrowPhase();

public:

	/*-------------- CONSTRUCTORS --------------*/

	PhysicWorld();
	static PhysicWorld* getInstance();

	/*-------------- METHODS---------------*/
	void runPhysics(float _duration);

	/*-------------- GETTERS --------------*/

	PhysicObject* getPhysicObject(int indexParticle);

	vector<PhysicObject*> getPhysicObjects();
	vector<RigidBody*> getRigidBodies();
	vector<Particle*> getParticles();

	int getNumberOfParticles();
	int getNumberOfRigidBodies();
	int getNumberOfPhysicObject();

	/*-------------- METHODS PARTICLES --------------*/
	/* Methods */

	void addParticle();
	void addParticle(Vector3D _initialPosition);

	/*-------------- METHODS RIGIDBODIES --------------*/

	void addRigidBody();
	void addRigidBody(Vector3D _initialPosition);
	void addRigidBody(Vector3D _initialPosition, Vector3D _scale);
	void addRigidBody(Vector3D _initialPosition, float _mass);

	void addRigidBody(RigidBody* rigidBody, Primitive* primitive);

	void removePhysicObject(PhysicObject* _target);
	void clearPhysicObjects();

	/*-------------- METHODS FORCES --------------*/

	void addForceEntry(PhysicObject* _newPhysicObject, ObjectForceGenerator* fg);
	void removeForceEntry(PhysicObject* _targetPhysicObject, ObjectForceGenerator* _targetForceGenerator);

	/*-------------- METHODS CONTACT GENERATOR --------------*/

	void addContactGenerator(ParticleContactGenerator* _contactGenerator);
	vector<CollisionData> getContacts();

	/*---------------METHODS PAUSE -------------------*/
	void Resume();
	void Pause();
};