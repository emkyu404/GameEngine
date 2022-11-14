#include "RigidSpringForceGenerator.h"

/*-------------- CONSTRUCTORS --------------*/

RigidSpringForceGenerator::RigidSpringForceGenerator(PhysicObject* _m_other, Vector3D _localAnchor, Vector3D _otherLocalAnchor)
	:SpringForceGenerator(m_other)
{
	m_bodyAnchor = _localAnchor; 
	m_otherBodyAnchor = _otherLocalAnchor; 
}

RigidSpringForceGenerator::RigidSpringForceGenerator(PhysicObject* _m_other, float m_k, float m_restLength, Vector3D _localAnchor, Vector3D _otherLocalAnchor) 
	:SpringForceGenerator(m_other, m_k, m_restLength)
{
	m_bodyAnchor = _localAnchor;
	m_otherBodyAnchor = _otherLocalAnchor;
}

/*-------------- METHODES --------------*/

void RigidSpringForceGenerator::updateForce(PhysicObject* _physicObject, float _duration) {

	RigidBody* _rigidbody = (RigidBody*) _physicObject; 

	Vector3D d = m_bodyAnchor - m_otherBodyAnchor; 
	Vector3D F = d.normalize() * -1 * m_k * abs((d.norm() - m_restLength));
	_rigidbody->addForceAtBodyPoint(F, m_bodyAnchor);
}