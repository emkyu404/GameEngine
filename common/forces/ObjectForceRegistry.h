#pragma once

#include <vector>
#include "ObjectForceGenerator.h"
#include "Particle.hpp"
#include "Vector3D.hpp"

using namespace std;

class ObjectForceRegistry
{
private:

	struct ObjectForceEntry
	{
		PhysicObject* object;
		ObjectForceGenerator* forceGenerator; 
	};

	using Registry = vector<ObjectForceEntry>;
	Registry m_registry;


public:

	/*-------------- METHODES --------------*/

	void updateForce(float _duration); 
	void addForceEntry(PhysicObject* _object, ObjectForceGenerator* _forceGenerator);
	void removeForceEntry(PhysicObject* _object, ObjectForceGenerator* _forceGenerator);
	void removeAllForceEntryForParticle(PhysicObject* _object);
	void clear();

};