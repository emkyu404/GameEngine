#include "ParticleDrag.h"
#include "ParticleForceGenerator.h"

/*-------------- CONSTRUCTORS --------------*/

ParticleDrag::ParticleDrag() 
	: ParticleDrag(DEFAULT_VALUE_K1, DEFAULT_VALUE_K2) 
{
}

ParticleDrag::ParticleDrag(float _m_k1, float _m_k2) {
	m_k1 = _m_k1; 
	m_k2 = _m_k2; 
}

/*-------------- METHODES --------------*/

void ParticleDrag::updateForce(Particle* _particle, float _duration) {
	Vector3D velocity = _particle->getVelocity(); 
	Vector3D F = velocity.normalize() * (m_k1 * velocity.norm() + m_k2 * velocity.norm()) * -1;
	_particle->addForce(F);
}