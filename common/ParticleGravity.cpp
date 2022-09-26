#include "ParticleGravity.h"
#include "ParticleForceGenerator.h"

void ParticleGravity::UpdateForce(Particle* _particle, float _duration)
{
	Vector3D F = m_gravity * _particle->GetMass();
	_particle->AddForce(F);
}
