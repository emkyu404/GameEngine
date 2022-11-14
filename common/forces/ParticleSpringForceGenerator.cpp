#include "ParticleSpringForceGenerator.h"

/*-------------- METHODES --------------*/

ParticleSpringForceGenerator::ParticleSpringForceGenerator(PhysicObject* _particle) : SpringForceGenerator() {
	Particle* particle = dynamic_cast<Particle*>(_particle);
	m_other = particle;
}

ParticleSpringForceGenerator::ParticleSpringForceGenerator(PhysicObject* _particle, float _m_k, float _m_restLength) : SpringForceGenerator(_m_k, _m_restLength) {
	Particle* particle = dynamic_cast<Particle*>(_particle);
	m_other = particle;
}

void ParticleSpringForceGenerator::updateForce(PhysicObject* _particle, float _duration) {
	Vector3D d = _particle->getPosition() - m_other->getPosition();
	Vector3D F = d.normalize() * -1 * m_k * abs((d.norm() - m_restLength));
	_particle->addForce(F);
}