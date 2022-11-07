#include "GravityForceGenerator.h"
#include "ObjectForceGenerator.h"

/*-------------- CONSTRUCTORS --------------*/

GravityForceGenerator::GravityForceGenerator() 
	: GravityForceGenerator(EARTH_GRAVITY)
{
}

GravityForceGenerator::GravityForceGenerator(Vector3D _gravity) {
	m_gravity = _gravity; 
}

/*-------------- METHODES --------------*/

void GravityForceGenerator::updateForce(PhysicObject* _particle, float _duration) {
	Vector3D F = m_gravity * _particle->getMass();
	_particle->addForce(F);
}
