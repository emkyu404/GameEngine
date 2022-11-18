#include "RigidSpringForceGenerator.h"

/*-------------- CONSTRUCTORS --------------*/

RigidSpringForceGenerator::RigidSpringForceGenerator(PhysicObject* _m_other, Vector3D _localAnchor, Vector3D _otherLocalAnchor)
	:SpringForceGenerator()
{
	RigidBody* rb = dynamic_cast<RigidBody*>(_m_other);
	m_other = rb;
	m_bodyAnchor = _localAnchor; 
	m_otherBodyAnchor = _otherLocalAnchor; 
}

RigidSpringForceGenerator::RigidSpringForceGenerator(PhysicObject* _m_other, float m_k, float m_restLength, Vector3D _localAnchor, Vector3D _otherLocalAnchor) 
	:SpringForceGenerator(m_k, m_restLength)
{
	RigidBody* rb = dynamic_cast<RigidBody*>(_m_other);
	m_other = rb;
	m_bodyAnchor = _localAnchor;
	m_otherBodyAnchor = _otherLocalAnchor;
}

/*-------------- METHODES --------------*/

void RigidSpringForceGenerator::updateForce(PhysicObject* _physicObject, float _duration) {

	RigidBody* _rigidbody = dynamic_cast<RigidBody*>(_physicObject);
	// Get world position of our anchors
	Vector3D m_bodyAnchorWorld = _rigidbody->getTransformMatrix().transformAll(m_bodyAnchor);
	Vector3D m_otherBodyAnchorWorld = m_other->getTransformMatrix().transformAll(m_otherBodyAnchor);

	// Calculate distance between our two anchors
	Vector3D d = m_bodyAnchorWorld - m_otherBodyAnchorWorld; 

	// Calculate force
	Vector3D F = (d.normalize() * -1) * m_k * abs((d.norm() - m_restLength));

	// Add force at body anchor point
	_rigidbody->addForceAtPoint(F, m_bodyAnchorWorld);
}