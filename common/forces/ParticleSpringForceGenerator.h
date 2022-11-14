#pragma once
#include "SpringForceGenerator.h"
#include "Vector3D.hpp"


class ParticleSpringForceGenerator : public SpringForceGenerator
{

protected:
	Particle* m_other;

public:

	ParticleSpringForceGenerator(PhysicObject* _particle);
	ParticleSpringForceGenerator(PhysicObject* _particle, float _m_k, float _m_restLength);
	
	/*-------------- METHODES --------------*/

	void updateForce(PhysicObject* particle, float duration);
};