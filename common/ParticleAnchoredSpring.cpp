#include "ParticleAnchoredSpring.h"
#include "ParticleForceGenerator.h"

/*-------------- CONSTRUCTORS --------------*/

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3D* _m_anchor)
	: ParticleAnchoredSpring(_m_anchor, DEFAULT_VALUE_K, DEFAULT_VALUE_RESTLENGTH)
{
}

ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3D* _m_anchor, float _k, float _restLength)
{
	m_anchor = _m_anchor;
	m_k = _k;
	m_restLength = _restLength;
}

/*-------------- METHODES --------------*/

void ParticleAnchoredSpring::UpdateForce(Particle* _particle, float _duration)
{
	Vector3D d = _particle->GetPosition() - *m_anchor; 
	Vector3D F = d.Normalize() * m_k * (m_restLength - d.Norm()) ;
	_particle->AddForce(F);
}