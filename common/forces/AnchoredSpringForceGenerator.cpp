#include "AnchoredSpringForceGenerator.h"
#include "ObjectForceGenerator.h"

/*-------------- CONSTRUCTORS --------------*/

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(Vector3D* _m_anchor)
	: AnchoredSpringForceGenerator(_m_anchor, DEFAULT_VALUE_K, DEFAULT_VALUE_RESTLENGTH)
{
}

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(Vector3D* _m_anchor, float _k, float _restLength) {
	m_anchor = _m_anchor;
	m_k = _k;
	m_restLength = _restLength;
}

/*-------------- METHODES --------------*/

void AnchoredSpringForceGenerator::updateForce(PhysicObject* _particle, float _duration) {
	Vector3D d = _particle->getPosition() - *m_anchor; 
	Vector3D F = d.normalize() * m_k * (m_restLength - d.norm()) ;
	_particle->addForce(F);
}