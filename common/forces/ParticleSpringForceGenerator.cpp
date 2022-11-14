#include "ParticleSpringForceGenerator.h"

/*-------------- METHODES --------------*/

void ParticleSpringForceGenerator::updateForce(PhysicObject* _particle, float _duration) {
	Vector3D d = _particle->getPosition() - m_other->getPosition();
	Vector3D F = d.normalize() * -1 * m_k * abs((d.norm() - m_restLength));
	_particle->addForce(F);
}