#include "ParticleDrag.h"
#include "ParticleForceGenerator.h"

/*-------------- CONSTRUCTORS --------------*/

ParticleDrag::ParticleDrag() 
	: ParticleDrag(DEFAULT_VALUE_K1, DEFAULT_VALUE_K2)
{
}

ParticleDrag::ParticleDrag(float _m_k1, float _m_k2)
{
	m_k1 = _m_k1; 
	m_k2 = _m_k2; 
}

/*-------------- METHODES --------------*/

void ParticleDrag::UpdateForce(Particle* _particle, float _duration)
{
	Vector3D velocity = _particle->GetVelocity(); 
	Vector3D F = velocity.Normalize() * (m_k1 * velocity.Norm() + m_k2 * velocity.Norm()) * -1;
	_particle->AddForce(F);
}
