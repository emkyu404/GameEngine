#include "Particle.hpp"
#include "ParticleForceGenerator.h"
#include "ParticleForceRegistry.h"

void ParticleForceRegistry::UpdateForce(float _duration)
{
	for (auto&& forceEntry : m_registry) {
		forceEntry.forceGenerator->UpdateForce(forceEntry.particle, _duration);
	}
}
