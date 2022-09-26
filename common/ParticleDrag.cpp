#include "ParticleDrag.h"
#include "ParticleForceGenerator.h"

void ParticleDrag::UpdateForce(Particle* _particle, float _duration)
{
	Vector3D velocity = _particle->GetVelocity(); 
	Vector3D F = velocity.normalize() * (m_k1 * velocity.norm() + m_k2 * velocity.norm()) * -1;
	_particle->AddForce(F);
}
