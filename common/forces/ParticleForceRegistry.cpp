#include "Particle.hpp"
#include "ParticleForceGenerator.h"
#include "ParticleForceRegistry.h"
#include <algorithm>

using namespace std;

void ParticleForceRegistry::UpdateForce(float _duration)
{
	if (m_registry.size() <= 0) {
		return;
	}
	for (auto&& forceEntry : m_registry) {
		forceEntry.forceGenerator->UpdateForce(forceEntry.particle, _duration);
	}
}

void ParticleForceRegistry::AddForceEntry(Particle* _particle, ParticleForceGenerator* _force) 
{
	ParticleForceEntry newForceEntry;
	newForceEntry.particle = _particle;
	newForceEntry.forceGenerator = _force;
	m_registry.push_back(newForceEntry);
}

void ParticleForceRegistry::RemoveForceEntry(Particle* _particle, ParticleForceGenerator* _force) 
{
	m_registry.erase(
		remove_if(
			m_registry.begin(), 
			m_registry.end(), 
			[&](const ParticleForceEntry& pfe) 
			{ return pfe.particle == _particle && pfe.forceGenerator == _force; 
			}),
		m_registry.end()
	);
}

void ParticleForceRegistry::RemoveAllForceEntryForParticle(Particle particle)
{
	/*
	m_registry.erase(remove_if(
		m_registry.begin(),
		m_registry.end(),
		[](ParticleForceEntry& pfe) { return pfe.particle == &particle; })
	))
	*/
}

void ParticleForceRegistry::Clear() {
	m_registry.clear();
}