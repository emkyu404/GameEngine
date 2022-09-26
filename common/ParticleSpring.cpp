#include "ParticleSpring.h"
#include "ParticleForceGenerator.h"

/*-------------- CONSTRUCTORS --------------*/

ParticleSpring::ParticleSpring(Particle* _m_other) 
	: ParticleSpring(_m_other, DEFAULT_VALUE_K, DEFAULT_VALUE_RESTLENGTH)
{
}

ParticleSpring::ParticleSpring(Particle* _m_other, float _k, float _restLength)
{
	m_other = _m_other; 
	m_k = _k; 
	m_restLength = _restLength; 
}

/*-------------- METHODES --------------*/

void ParticleSpring::UpdateForce(Particle* _particle, float _duration)
{
	Vector3D d = _particle->GetPosition() - m_other->GetPosition(); 
	Vector3D F = d.Normalize() * m_k * -1 * (d.Norm() - m_restLength);
	_particle->AddForce(F);
}