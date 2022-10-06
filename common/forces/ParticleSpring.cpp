#include "ParticleSpring.h"
#include "ParticleForceGenerator.h"

/*-------------- CONSTRUCTORS --------------*/

ParticleSpring::ParticleSpring(Particle* _m_other) 
	: ParticleSpring(_m_other, DEFAULT_VALUE_K, DEFAULT_VALUE_RESTLENGTH)
{
}

ParticleSpring::ParticleSpring(Particle* _m_other, float _k, float _restLength) {
	m_other = _m_other; 
	m_k = _k; 
	m_restLength = _restLength; 
}

/*-------------- METHODES --------------*/

void ParticleSpring::updateForce(Particle* _particle, float _duration) {
	Vector3D d = _particle->getPosition() - m_other->getPosition(); 
	Vector3D F = d.normalize() * -1 * m_k * abs((d.norm() - m_restLength));
	_particle->addForce(F);
}