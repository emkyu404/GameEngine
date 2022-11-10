#include "DragForceGenerator.h"
#include "ObjectForceGenerator.h"

/*-------------- CONSTRUCTORS --------------*/

DragForceGenerator::DragForceGenerator() 
	: DragForceGenerator(DEFAULT_VALUE_K1, DEFAULT_VALUE_K2) 
{
}

DragForceGenerator::DragForceGenerator(float _m_k1, float _m_k2) {
	m_k1 = _m_k1; 
	m_k2 = _m_k2; 
}

/*-------------- METHODES --------------*/

void DragForceGenerator::updateForce(PhysicObject* _particle, float _duration) {
	Vector3D velocity = _particle->getVelocity(); 
	Vector3D F = velocity.normalize() * (m_k1 * velocity.norm() + m_k2 * velocity.norm()) * -1;
	_particle->addForce(F);
}
