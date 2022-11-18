#include "Particle.hpp"
#include "ObjectForceGenerator.h"
#include "ObjectForceRegistry.h"
#include <algorithm>

using namespace std;

void ObjectForceRegistry::updateForce(float _duration) {
	if (m_registry.size() <= 0) {
		return;
	}
	for (auto&& forceEntry : m_registry) {
		forceEntry.forceGenerator->updateForce(forceEntry.object, _duration);
	}
}

void ObjectForceRegistry::addForceEntry(PhysicObject* _particle, ObjectForceGenerator* _force) {
	ObjectForceEntry newForceEntry;
	newForceEntry.object = _particle;
	newForceEntry.forceGenerator = _force;
	m_registry.push_back(newForceEntry);
}

void ObjectForceRegistry::removeForceEntry(PhysicObject* _object, ObjectForceGenerator* _force) {
	m_registry.erase(
		remove_if(
			m_registry.begin(), 
			m_registry.end(), 
			[&](const ObjectForceEntry& pfe) 
			{ return pfe.object == _object && pfe.forceGenerator == _force;
			}),
		m_registry.end()
	);
}


void ObjectForceRegistry::removeAllForceEntryForPhysicObject(PhysicObject* _object) {
	m_registry.erase(
		remove_if(
			m_registry.begin(),
			m_registry.end(),
			[&](const ObjectForceEntry& pfe)
			{ return pfe.object == _object;
			}),
		m_registry.end()
				);
}

void ObjectForceRegistry::clear() {
	m_registry.clear();
}